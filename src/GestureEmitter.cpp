#include <linux/input.h>
#include "Gesture.cpp"

using namespace std;
class GestureEmitter
{
public:
    Gesture *gesture;
    GestureEmitter()
    {
        this->gesture = new Gesture();
    }

    Gesture *emit(input_event &event)
    {

        return gesture;
    }
};