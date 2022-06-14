#ifndef __GESTUREPOSITION_H__
#define __GESTUREPOSITION_H__

#include <iostream>

enum class GesturePosition
{
    left,
    right,
    top,
    bottom,
    middle,
    undefined
};

inline std::ostream &operator<<(std::ostream &stream, const GesturePosition position)
{
    switch (position)
    {
    case GesturePosition::top:
        stream << "TOP";
        break;
    case GesturePosition::bottom:
        stream << "BOTTOM";
        break;
    case GesturePosition::left:
        stream << "LEFT";
        break;
    case GesturePosition::right:
        stream << "RIGHT";
        break;
    case GesturePosition::middle:
        stream << "MIDDLE";
        break;
    case GesturePosition::undefined:
        stream << "IDLE/NONE";
        break;
    }
    return stream;
}
#endif // __GESTUREPOSITION_H__
