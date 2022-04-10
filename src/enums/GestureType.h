#ifndef __GESTURETYPE_H__
#define __GESTURETYPE_H__

#include <iostream>

enum class GestureType
{
    swipe,
    tap,
    pinch,
    idle
};

inline std::ostream &operator<<(std::ostream &stream, const GestureType type)
{
    switch (type)
    {
    case GestureType::swipe:
        stream << "TOP";
        break;
    case GestureType::tap:
        stream << "BOTTOM";
        break;
    case GestureType::pinch:
        stream << "LEFT";
        break;
    case GestureType::idle:
        stream << "IDLE/NONE";
        break;
    }
    return stream;
}
#endif // __GESTURETYPE_H__