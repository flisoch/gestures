#include "EventHandler.h"
#include "Finger.h"

EventHandler::EventHandler() {}
int EventHandler::put(input_event &ev)
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
                current_slot = ev.value;
            }
            gesture.add_finger(current_slot, new Finger());
        }
    }
    else if (ev.code == ABS_MT_POSITION_X)
    {
        gesture.move_finger("x", current_slot, ev.value, ev.time);
        gesture.try_perform(current_slot);
    }
    else if (ev.code == ABS_MT_POSITION_Y)
    {
        gesture.move_finger("y", current_slot, ev.value, ev.time);
        gesture.try_perform(current_slot);
    }

    return 1;
}
