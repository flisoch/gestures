#include "Gesture.h"
#include "Config.h"
#include "enums/GestureDirection.h"
#include "enums/GesturePosition.h"
#include <thread>
#include <iostream>

Gesture::Gesture() {}
void Gesture::add_finger(int slot, Finger *finger)
{
    finger_slots.insert({slot, finger});
    this->phase = Phase::start;
}

void Gesture::move_finger(const std::string axis, int slot, int value, timeval update_time)
{
    Finger *finger = finger_slots.at(slot);
    if (axis == "x") {
        int prev_update = finger->x_update;
        finger->move_x(value);
        this->total_update_x += finger->x_update - prev_update;
    }
    else if (axis == "y") {
        int prev_update = finger->y_update;
        finger->move_y(value);
        this->total_update_y += finger->y_update - prev_update;
    }

    int update_power = finger->x_update * finger->x_update + finger->y_update * finger->y_update;
    if (!finger->moved) {
        if (update_power > THRESHOLD_SQUARED)
        {
            // std::cout << finger->x_update << "^2 + " << finger->y_update << "^2 = " << threshold << " > " << THRESHOLD_SQUARED << std::endl;
            finger->moved = true;
            this->fingers_moved += 1;
        }
    }

    double now_time = update_time.tv_sec + (update_time.tv_usec / 1000000.0);
    if (this->time_since_last_performance < DEBOUNCE)
    {
        this->time_since_last_performance = now_time - this->update_time;
    }
    this->update_time = now_time;
}


void Gesture::measure_direction(int slot) {
    //total
    int x_update = finger_slots[slot]->x_update;
    int y_update = finger_slots[slot]->y_update;
    int x_update_total = abs(total_update_x);
    int y_update_total = abs(total_update_y);

    if (y_update_total <= x_update_total * tan(ANGLE_X * M_PI / 180))
    {
        // horizontal
        if (x_update <= 0)
        {
            this->direction = GestureDirection::left;
        }
        else
        {
            this->direction = GestureDirection::right;
        }
    }
    else if (y_update_total >= x_update_total * tan((90 - ANGLE_X) * M_PI / 180))
    {
        // vertical
        std::cout << "y-cum : " << y_update << std::endl;
        if (y_update <= 0)
        {
            std::cout << "y-cum : " << y_update << std::endl;
            this->direction = GestureDirection::up;
        }
        else
        {
            this->direction = GestureDirection::down;
        }
    }
    else
    {
        if (x_update * y_update > 0)
        {
            if (x_update <= 0 and y_update < 0)
            {
                this->direction = GestureDirection::up_left;
            }
            if (x_update > 0 and y_update >= 0)
            {
                this->direction = GestureDirection::down_right;
            }
        }
        if (x_update * y_update < 0)
        {

            if (x_update >= 0 and y_update < 0)
            {
                this->direction = GestureDirection::up_right;
            }
            if (x_update < 0 and y_update >= 0)
            {
                this->direction = GestureDirection::down_left;
            }
        }
    }
}

void Gesture::clear(int slot)
    {
        phase = Phase::end;
        try_perform(slot);
        finger_slots.erase(slot);
        fingers_moved = 0;
        total_update_x = 0;
        total_update_y = 0;
        position = GesturePosition::idle;
        direction = GestureDirection::idle;
        std::cout << "ERASING" << std::endl;
    }

void Gesture::clear_updates()
    {
        fingers_moved = 0;
        for ( const auto &[key, value]: finger_slots ) {
            value->x_update = 0;
            value->y_update = 0;
            value->moved = false;
        }
    }

void Gesture::try_perform(int slot)
{
    int fingers_count = this->finger_slots.size();
    // std::cout << "fingers count: " << fingers_count << " moved: " << fingers_moved << std::endl;
    if (fingers_count == this->fingers_moved || this->phase == Phase::end) {
        measure_direction(slot);
        measure_position(slot);
        std::thread t1(&Gesture::call, this);
        // t1.detach();
        // 2-3 commands/Fires lag if detach thread so now Main waits for excecution of command/thread
        t1.join();
        clear_updates();
    }
}

void Gesture::measure_position(int slot)
{
    if (finger_slots.size() == 1)
        {

            int abs_x = finger_slots[slot]->abs_x;
            int abs_y = finger_slots[slot]->abs_y;

            if (abs_x < 100)
            {
                this->position = GesturePosition::left;
            }
            else if (abs_x > 1119)
            {
                this->position = GesturePosition::right;
            }
            else if (abs_y < 150)
            {
                this->position = GesturePosition::top;
            }
            else if (abs_y > 609)
            {
                this->position = GesturePosition::bottom;
            }
        }
}

void Gesture::call()
{
    GesturePosition position = this->position;
    GestureDirection direction = this->direction;
    Phase phase = this->phase;
    std::cout << "DIRECTION: " << direction << std::endl;
    std::cout << "POSITION: " << position << std::endl;
    std::cout << "PHASE: " << phase << std::endl;
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
        // todo: calculate direction more precicely as edge-righ sometimes is up_right or down_right
        if (direction == GestureDirection::right || direction == GestureDirection::up_right || direction == GestureDirection::down_right)
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
        else if (direction == GestureDirection::left || direction == GestureDirection::up_left || direction == GestureDirection::down_left)
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
    if (phase == Phase::start)
    {
        this->phase = Phase::update;
    }
    this->time_since_last_performance = 0;
}

std::ostream &operator<<(std::ostream &stream, const Gesture gesture)
{
    stream << "fingers moved: " << gesture.fingers_moved << ", phase: " << gesture.phase << std::endl;
    return stream;
}