#include "EventHandler.h"
#include "Finger.h"

// EventHandler::EventHandler() {}
int EventHandler::put(input_event &ev)
{
    if (ev.code == ABS_MT_SLOT)
    {
        //std::cout << "ABS_MT_SLOT\n";
        current_slot = ev.value;
    }
    else if (ev.code == ABS_MT_TRACKING_ID)
    {
        //std::cout << "ABS_MT_TRACKING_ID\n";
        if (ev.value == -1)
        {
            gesture.try_perform(current_slot);
            gesture.clear(current_slot);
            current_slot = -1;
        }
        else
        {
            if (current_slot == -1)
            {
                current_slot = 0;
            }
            gesture.add_finger(current_slot);
        }
    }
    else if (ev.code == ABS_MT_POSITION_X)
    {
        // std::cout << "ABS_MT_POSITION_X\n";
        gesture.move_finger("x", current_slot, ev.value, ev.time);
        gesture.try_perform(current_slot);
    }
    else if (ev.code == ABS_MT_POSITION_Y)
    {
        // std::cout << "ABS_MT_POSITION_Y\n";
        gesture.move_finger("y", current_slot, ev.value, ev.time);
        gesture.try_perform(current_slot);
    }

    return 1;
}
