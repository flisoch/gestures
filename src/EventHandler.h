#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__


#include <linux/input.h>
#include <iostream>
#include "Gesture.h"


class EventHandler
{
private:
    int current_slot = -1;
    Gesture gesture;

public:
    int put(input_event &ev);
};

#endif // __EVENTHANDLER_H__