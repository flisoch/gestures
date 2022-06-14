#ifndef __CONFIG_H__
#define __CONFIG_H__

#define DEBOUNCE 0.06
#define THRESHOLD_SQUARED 40 // threshold to be considered a move, squared sum of x and y
#define DECISION = 75        // sufficient movement to make decision on direction, scaled by the number of slots
#define ANGLE_X 16           // angle to interpret as horizontal
#define ANGLE_Y 21           // angle to interpret as vertical

#endif // __CONFIG_H__
