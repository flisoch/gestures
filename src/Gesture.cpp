#include "Gesture.h"
#include "Config.h"
#include "enums/GestureDirection.h"
#include "enums/GesturePosition.h"
#include <thread>
#include <iostream>

void Gesture::init_config(libconfig::Config &cfg)
{
    try
    {
        cfg.readFile("/home/flisoch/cpp/gestures/build/gestures.cfg");
    }
    catch (const libconfig::FileIOException &fioex)
    {
        std::cerr << "I/O error while reading file: " << fioex.what() << std::endl;
        throw fioex;
    }
    catch (const libconfig::ParseException &pex)
    {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        throw pex;
    }
}

Gesture::Gesture()
{
    try
    {
        init_config(cfg);
    }
    catch (std::exception &e)
    {
        throw e;
    }
}

void Gesture::add_finger(int slot)
{
    finger_slots.insert({slot, Finger()});
    phase = Phase::start;
}

void Gesture::move_finger(const std::string axis, int slot, int value, timeval time)
{
    Finger &finger = finger_slots.at(slot);
    if (axis == "x")
    {
        int prev_update = finger.x_update;
        finger.move_x(value);
        total_update_x += finger.x_update - prev_update;
    }
    else if (axis == "y")
    {
        int prev_update = finger.y_update;
        finger.move_y(value);
        total_update_y += finger.y_update - prev_update;
    }

    int update_power = finger.x_update * finger.x_update + finger.y_update * finger.y_update;
    if (!finger.moved)
    {
        if (update_power > THRESHOLD_SQUARED)
        {
            // std::cout << finger.x_update << "^2 + " << finger.y_update << "^2 = " << threshold << " > " << THRESHOLD_SQUARED << std::endl;
            finger.moved = true;
            fingers_moved += 1;
        }
    }

    double now_time = time.tv_sec + (time.tv_usec / 1000000.0);
    if (time_since_last_performance < DEBOUNCE)
    {
        time_since_last_performance = now_time - update_time;
    }
    update_time = now_time;
}

void Gesture::measure_direction(int slot)
{
    // total
    int x_update = finger_slots[slot].x_update;
    int y_update = finger_slots[slot].y_update;
    int x_update_total = abs(total_update_x);
    int y_update_total = abs(total_update_y);

    if (y_update_total <= x_update_total * tan(ANGLE_X * M_PI / 180))
    {
        // horizontal
        if (x_update <= 0)
        {
            direction = GestureDirection::left;
        }
        else
        {
            direction = GestureDirection::right;
        }
    }
    else if (y_update_total >= x_update_total * tan((90 - ANGLE_X) * M_PI / 180))
    {
        // vertical
        std::cout << "y-cum : " << y_update << std::endl;
        if (y_update <= 0)
        {
            std::cout << "y-cum : " << y_update << std::endl;
            direction = GestureDirection::up;
        }
        else
        {
            direction = GestureDirection::down;
        }
    }
    else
    {
        if (x_update * y_update > 0)
        {
            if (x_update <= 0 and y_update < 0)
            {
                direction = GestureDirection::left_up;
            }
            if (x_update > 0 and y_update >= 0)
            {
                direction = GestureDirection::right_down;
            }
        }
        if (x_update * y_update < 0)
        {

            if (x_update >= 0 and y_update < 0)
            {
                direction = GestureDirection::right_up;
            }
            if (x_update < 0 and y_update >= 0)
            {
                direction = GestureDirection::left_down;
            }
        }
    }
}

void Gesture::clear(int slot)
{
    phase = Phase::end;
    finger_slots.erase(slot);
    fingers_moved = 0;
    total_update_x = 0;
    total_update_y = 0;
    position = GesturePosition::undefined;
    direction = GestureDirection::undefined;
    time_since_last_performance = 0;
    update_time = 0;
    std::cout << "ERASING" << std::endl;
}

void Gesture::clear_updates()
{
    fingers_moved = 0;
    for (auto &[key, value] : finger_slots)
    {
        value.x_update = 0;
        value.y_update = 0;
        value.moved = false;
    }
}

void Gesture::try_perform(int slot)
{
    int fingers_count = finger_slots.size();
    // std::cout << "fingers count: " << fingers_count << " moved: " << fingers_moved << std::endl;
    if (fingers_count == fingers_moved || phase == Phase::end)
    {
        measure_direction(slot);
        measure_position(slot);
        call();
        // t1.detach();
        // 2-3 commands/Fires lag if detach thread so now Main waits for excecution of command/thread
        clear_updates();
    }
}

void Gesture::measure_position(int slot)
{
    if (finger_slots.size() == 1)
    {

        int abs_x = finger_slots[slot].abs_x;
        int abs_y = finger_slots[slot].abs_y;

        if (abs_x < 100)
        {
            position = GesturePosition::left;
        }
        else if (abs_x > 1119)
        {
            position = GesturePosition::right;
        }
        else if (abs_y < 150)
        {
            position = GesturePosition::top;
        }
        else if (abs_y > 609)
        {
            position = GesturePosition::bottom;
        }
    }
}

void Gesture::call()
{
    std::cout << "DIRECTION: " << direction << std::endl;
    std::cout << "POSITION: " << position << std::endl;
    std::cout << "PHASE: " << phase << std::endl;
    if (finger_slots.size() == 1)
    {
        execute_one_finger_gesture();
    }
    else
    {
        execute_multitouch_gesture();
    }

    if (phase == Phase::start)
    {
        phase = Phase::update;
    }
    time_since_last_performance = 0;
}

void Gesture::execute_multitouch_gesture()
{
    const libconfig::Setting &root = cfg.getRoot();
    if (type == GestureType::swipe && fingers_moved > 0)
    {
        std::string fingers_moved_str = int_to_string(fingers_moved);
        const libconfig::Setting &swipes = root["swipe"];
        const libconfig::Setting &one = swipes["one"];
        if(fingers_moved == 1 || fingers_moved == 2) {
            return;
        }
        try
        {
            const libconfig::Setting &commands = root["swipe"][fingers_moved_str][to_string(direction)];
            std::string command;
            if (commands.lookupValue(to_string(phase), command))
            {
                system(command.c_str());
            }
        }
        catch (std::exception &e)
        {
            std::cerr << e.what();
        }
    }
}

void Gesture::execute_one_finger_gesture()
{
    if (position == GesturePosition::left)
    {
        if (direction == GestureDirection::down)
        {
            if (phase == Phase::start)
            {
                system("xte \'key XF86MonBrightnessDown\'");
            }
            else if (phase == Phase::update)
            {
                system("xte \'key XF86MonBrightnessDown\'");
            }
            else if (phase == Phase::end)
            {
                system("xte \'key XF86MonBrightnessDown\'");
            }
        }
        else if (direction == GestureDirection::up)
        {

            system("xte \'key XF86MonBrightnessUp\'");
        }
        std::cout << "FIRE!" << std::endl;
    }
    else if (position == GesturePosition::right)
    {
        if (direction == GestureDirection::down)
        {
            system("xte \'key XF86AudioLowerVolume\'");
        }
        if (direction == GestureDirection::up)
        {
            system("xte \'key XF86AudioRaiseVolume\'");
        }
        std::cout << "FIRE!" << std::endl;
    }
    else if (position == GesturePosition::bottom)
    {
        // todo: calculate direction more precicely as edge-righ sometimes is right_up or right_down
        if (direction == GestureDirection::right || direction == GestureDirection::right_up || direction == GestureDirection::right_down)
        {
            if (phase == Phase::start)
            {
                system("xte \'keydown Alt_L\' \'key Tab\'");
                std::cout << "xte \'keydown Alt_L\' \'key Tab\'" << std::endl;
            }
            else if (phase == Phase::update)
            {
                std::cout << "xte \'key Right\'" << std::endl;
                system("xte \'key Right\'");
            }
            else if (phase == Phase::end)
            {
                std::cout << "xte \'keyup Alt_L\'" << std::endl;

                system("xte \'keyup Alt_L\'");
            }
        }
        else if (direction == GestureDirection::left || direction == GestureDirection::left_up || direction == GestureDirection::left_down)
        {

            if (phase == Phase::start)
            {

                system("xte \'keydown Alt_L\'");
                system("xte \'key Tab\'");
                std::cout << "xte \'keydown Alt_L\' \'key Tab\'" << std::endl;
            }
            else if (phase == Phase::update)
            {
                system("xte \'key Left\'");
            }
            else if (phase == Phase::end)
            {
                system("xte \'keyup Alt_L\'");
            }
        }

        std::cout << "FIRE!" << std::endl;
    }
}

std::ostream &operator<<(std::ostream &stream, const Gesture gesture)
{
    stream << "fingers moved: " << gesture.fingers_moved << ", phase: " << gesture.phase << std::endl;
    return stream;
}