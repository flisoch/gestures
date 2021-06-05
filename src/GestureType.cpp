#include <iostream>
#include <type_traits>

enum class GestureType
{
    swipe,
    tap,
    pinch,
    idle
};

std::ostream &operator<<(std::ostream &stream, const GestureType type)
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