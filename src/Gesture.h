#ifndef __GESTURE_H__
#define __GESTURE_H__

#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <math.h>
#include <thread>

#include "enums/GestureDirection.h"
#include "enums/GesturePosition.h"
#include "enums/GestureType.h"
#include "enums/Phase.h"
#include "Finger.h"

class Gesture
{

public:
    std::map<int, Finger *> finger_slots;
    int fingers_moved;
    GestureDirection direction;
    GesturePosition position;
    GestureType type = GestureType::swipe;
    Phase phase;

    int total_update_x; //x update of all fingers
    int total_update_y; //y update of all fingers
    double time_since_last_performance;
    double update_time; // time of last x/y update of any finger

    Gesture();

    void add_finger(int slot, Finger *finger);
    void move_finger(const std::string axis, int slot, int value, timeval update_time);
    void try_perform(int slot);
    void measure_position(int slot);
    void measure_direction(int slot);
    void call();
    void clear(int slot);
    void clear_updates();
};

#endif // __GESTURE_H__