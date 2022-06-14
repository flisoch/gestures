#ifndef __GESTUREDIRECTION_H__
#define __GESTUREDIRECTION_H__

#include <iostream>

enum class GestureDirection
{
    up,
    down,
    left,
    right,
    right_up,
    left_up,
    right_down,
    left_down,
    undefined
};

inline std::ostream &operator<<(std::ostream &stream, const GestureDirection direction)
{
    switch (direction)
    {
    case GestureDirection::up:
        stream << "UP";
        break;
    case GestureDirection::down:
        stream << "DOWN";
        break;
    case GestureDirection::left:
        stream << "LEFT";
        break;
    case GestureDirection::right:
        stream << "RIGHT";
        break;
    case GestureDirection::right_up:
        stream << "RIGHT-UP";
        break;
    case GestureDirection::left_up:
        stream << "LEFT-UP";
        break;
    case GestureDirection::right_down:
        stream << "RIGHT-DOWN";
        break;
    case GestureDirection::left_down:
        stream << "LEFT-DOWN";
        break;
    case GestureDirection::undefined:
        stream << "IDLE/NONE";
        break;
    }
    return stream;
}

inline std::string to_string(GestureDirection GestureDirection) {
  switch (GestureDirection) {
    case GestureDirection::up:   return "up";
    case GestureDirection::down: return "down";
    case GestureDirection::left:  return "left";
    case GestureDirection::right: return "right";
    case GestureDirection::right_up:   return "right_up";
    case GestureDirection::left_up: return "left_up";
    case GestureDirection::right_down:  return "right_down";
    case GestureDirection::left_down: return "left_down";
    default: return "undefined";
  }
  return "undefined";
}
#endif // __GESTUREDIRECTION_H__
