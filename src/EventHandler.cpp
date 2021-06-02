#include <linux/input.h>
#include <iostream>
#include "Finger.cpp"
#include "Phase.cpp"
#include <map>

using namespace std;
class EventHandler
{
private:
    map<int, Finger *> slots;
    int current_slot;
    Phase phase = Phase::idle;

public:
    int put(input_event &ev)
    {
        if (ev.code == ABS_MT_SLOT)
        {
            current_slot = ev.value;
        }
        else if (ev.code == ABS_MT_TRACKING_ID)
        {
            if (ev.value == -1)
            {
                // clear finger and current gesture
                slots.erase(current_slot);
            }
            else
            {
                // add new finger
                if (current_slot == -1)
                {
                    current_slot = 0;
                }
                slots.insert({current_slot, new Finger()});
            }
        }
        else if (ev.code == ABS_MT_POSITION_X || ev.code == ABS_MT_POSITION_Y)
        {
            if (current_slot == -1)
            {
                // one finger handling for edge gestures
            }
            else
            {
                // update finger position
                Finger *finger = slots.at(current_slot);
                if (ev.code == ABS_MT_POSITION_X)
                {
                    finger->abs_x = ev.value;
                }
                else if (ev.code == ABS_MT_POSITION_Y)
                {
                    finger->abs_y = ev.value;
                }
                phase == Phase::update;
                cout << "Slot: " << current_slot;
                cout << finger->to_string() << endl;
            }
        }

        if (phase == Phase::update)
        {
            phase == Phase::idle;
            // flush data to gesture queue handler
        }
        return 1;
    }
};