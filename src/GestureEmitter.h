#ifndef __GESTUREEMITTER_H__
#define __GESTUREEMITTER_H__

#include <linux/input.h>
#include "Gesture.h"

class GestureEmitter
{
public:
    Gesture *gesture;
    GestureEmitter();
    Gesture *emit(input_event &event);
};
#endif // __GESTUREEMITTER_H__