#include <linux/input.h>
#include <iostream>
#include "Finger.cpp"
#include "Phase.cpp"
#include "Gesture.cpp"

using namespace std;
class EventHandler
{
private:
    int current_slot;
    Gesture gesture = Gesture();

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
                gesture.clear(current_slot);
            }
            else
            {
                // add new finger
                if (current_slot == -1)
                {
                    current_slot = 0;
                }
                gesture.add_finger(current_slot, new Finger());
            }
        }
        else if (ev.code == ABS_MT_POSITION_X)
        {
            if (current_slot == -1)
            {
                // one finger handling for edge gestures
                current_slot = 0;
            }
            gesture.move_finger("x", current_slot, ev.value);
            gesture.update();
            gesture.clear_updates();
        }
        else if (ev.code == ABS_MT_POSITION_Y)
        {
            if (current_slot == -1)
            {
                // one finger handling for edge gestures
                current_slot = 0;
            }
            gesture.move_finger("y", current_slot, ev.value);
            gesture.update();
            gesture.clear_updates();

        }

        return 1;
    }
};