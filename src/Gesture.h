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
#include "libconfig.h++"

class Gesture
{

public:
    libconfig::Config cfg;
    std::map<int, Finger> finger_slots;
    int fingers_moved = 0;
    GestureDirection direction = GestureDirection::undefined;
    GesturePosition position = GesturePosition::undefined;
    GestureType type = GestureType::swipe;
    Phase phase = Phase::undefined;

    int total_update_x = 0; // x update of all fingers
    int total_update_y = 0; // y update of all fingers
    double time_since_last_performance = 0;
    double update_time = 0; // time of last x/y update of any finger

    Gesture();
    // Gesture(Gesture&) = default;
    // Gesture(Gesture&&) = default;
    //~Gesture() = default;

    void init_config(libconfig::Config &cfg);
    void add_finger(int slot);
    void move_finger(const std::string axis, int slot, int value, timeval time);
    void try_perform(int slot);
    void measure_position(int slot);
    void measure_direction(int slot);
    void call();
    void clear(int slot);
    void clear_updates();
    void execute_one_finger_gesture();
    void execute_multitouch_gesture();

    std::string int_to_string(int fingers_moved)
    {
        switch (fingers_moved)
        {
        case 1:
            return "one";
        case 2:
            return "two";
        case 3:
            return "three";
        case 4:
            return "four";
        case 5:
            return "five";
        default:
            return "undefined";
        }
    }
};

#endif // __GESTURE_H__