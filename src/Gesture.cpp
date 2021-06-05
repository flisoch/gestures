
#include "GesturePosition.cpp"
#include "GestureDirection.cpp"
#include "GestureType.cpp"
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <math.h>
#include <thread>
// #include <pthread.h>

#define DEBOUNCE 0.04
#define THRESHOLD_SQUARED 30 // threshold to be considered a move, squared sum of x and y
#define DECISION = 75        // sufficient movement to make decision on direction, scaled by the number of slots
#define ANGLE_X 16           // angle to interpret as horizontal
#define ANGLE_Y 21           // angle to interpret as vertical

using namespace std;

class Gesture
{

public:
    int fingers_moved;
    GestureDirection direction;
    GesturePosition position;
    GestureType type = GestureType::swipe;
    string start_command;
    string update_command;
    string end_command;
    Phase phase;

    int total_update_x;
    int total_update_y;

    bool ready = false;
    map<int, Finger *> slots;

    Gesture()
    {
    }

    Gesture(vector<Finger> fingers, string start_command, Phase phase)
    {
        this->start_command = start_command;
    }

    string to_string() const
    {
        return "command: " + start_command + "\n";
    }

    void end()
    {
        fingers_moved = 0;
        start_command = "";
        update_command = "";
        end_command = "";
    }

    void definePosition(int abs_x, int abs_y)
    {
        //Todo: rewrite in relative values
        if ((abs_x < 100 || abs_x > 1120) && (abs_y < 100 || abs_y))
        {
            position = GesturePosition::left;
        }
        else
        {
            position = GesturePosition::middle;
        }
    }

    void defineDirection(int x_prev, int x_new, int y_prev, int y_new)
    {
    }

    void add_finger(int slot, Finger *finger)
    {
        slots.insert({slot, finger});
    }
    void perform()
    {

        GesturePosition position = this->position;
        GestureDirection direction = this->direction;
        cout << "DIRECTION: " << direction << endl;
        cout << "POSITION: " << position << endl;

        if (position == GesturePosition::left)
        {
            if (direction == GestureDirection::down)
            {
                system("xte \'key XF86MonBrightnessDown\'");
                cout << "lef & down = BrightnessDown" << endl;
            }
            else if (direction == GestureDirection::up)
            {

                system("xte \'key XF86MonBrightnessUp\'");
            }
            cout << "FIRE!" << endl;
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
            cout << "FIRE!" << endl;
        }
    }

    void move_finger(const string axis, int slot, int value)
    {
        Finger *finger = slots.at(slot);
        if (axis == "x")
        {
            finger->move_x(value);
            total_update_x += finger->x_update;
        }
        else if (axis == "y")
        {
            finger->move_y(value);
            total_update_y += finger->y_update;
        }

        int thr = finger->x_update * finger->x_update + finger->y_update * finger->y_update;
        if (thr > THRESHOLD_SQUARED)
        {
            cout << finger->x_update << "^2 + " << finger->y_update << "^2 = " << thr << " > " << THRESHOLD_SQUARED << endl;
            fingers_moved += 1;
        }
    }
    void clear(int slot)
    {
        slots.erase(slot);
        fingers_moved = 0;
        total_update_x = 0;
        total_update_y = 0;
        position = GesturePosition::idle;
        direction = GestureDirection::idle;
        cout << "ERASING" << endl;
    }
    void update()
    {
        int fingers_count = slots.size();
        if (!ready)
        {
            // cout << "fingers count: " << fingers_count << " moved: " << fingers_moved << endl;
            if (fingers_count == fingers_moved)
            {

                if (fingers_count == 3)
                {
                    cout << "3 fingers!";
                }
                else if (fingers_count == 1)
                {
                    int abs_x = slots[0]->abs_x;
                    int abs_y = slots[0]->abs_y;
                    //total
                    int x_update = slots[0]->x_update;
                    int y_update = slots[0]->y_update;
                    int x_update_total = abs(total_update_x);
                    int y_update_total = abs(total_update_y);

                    if (abs_x < 100)
                    {
                        this->position = GesturePosition::left;
                    }
                    else if (abs_x > 1119)
                    {
                        this->position = GesturePosition::right;
                    }
                    else if (abs_y < 100)
                    {
                        this->position = GesturePosition::top;
                    }
                    else if (abs_y > 699)
                    {
                        this->position = GesturePosition::bottom;
                    }

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
                        cout << "y-cum : " << y_update << endl;
                        if (y_update <= 0)
                        {
                            cout << "y-cum : " << y_update << endl;
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

                    //perform gesture in new thread
                    thread t1(&Gesture::perform, this);
                    // t1.detach();
                    // 2-3 commands/Fires lag if detach thread so now Main waits for excecution of command/thread
                    t1.join();
                    
                }
            }
        }
    }

    void clear_updates()
    {
        fingers_moved = 0;
        int fingers_count = slots.size();
        for (int i = 0; i < fingers_count; i++)
        {
            slots.at(i)->x_updates = 0;
            slots.at(i)->y_updates = 0;
            slots.at(i)->x_update = 0;
            slots.at(i)->y_updates = 0;
        }
    }
};