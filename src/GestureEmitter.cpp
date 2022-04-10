#include "GestureEmitter.h"


GestureEmitter::GestureEmitter()
{
    this->gesture = new Gesture();
}

Gesture* GestureEmitter::emit(input_event &event)
{
    return gesture;
}