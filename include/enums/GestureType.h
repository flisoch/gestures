#ifndef __GESTURETYPE_H__
#define __GESTURETYPE_H__

#include <iostream>

enum class GestureType
{
    swipe,
    tap,
    pinch,
    undefined
};

inline std::ostream &operator<<(std::ostream &stream, const GestureType type)
{
    switch (type)
    {
    case GestureType::swipe:
        stream << "swipe";
        break;
    case GestureType::tap:
        stream << "tap";
        break;
    case GestureType::pinch:
        stream << "pinch";
        break;
    case GestureType::undefined:
        stream << "undefined";
        break;
    }
    return stream;
}

inline std::string to_string(GestureType gesture) {
  switch (gesture) {
    case GestureType::swipe:   return "swipe";
    case GestureType::tap: return "tap";
    case GestureType::pinch:  return "pinch";
    case GestureType::undefined: return "undefined";
  }
}
#endif // __GESTURETYPE_H__
