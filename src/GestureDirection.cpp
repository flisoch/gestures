
enum class GestureDirection
{
    up,
    down,
    left,
    right,
    up_right,
    up_left,
    down_right,
    down_left,
    idle
};

std::ostream &operator<<(std::ostream &stream, const GestureDirection direction)
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
    case GestureDirection::up_right:
        stream << "UP-RIGHT";
        break;
    case GestureDirection::up_left:
        stream << "UP-LEFT";
        break;
    case GestureDirection::down_right:
        stream << "DOWN-RIGHT";
        break;
    case GestureDirection::down_left:
        stream << "DOWN-LEFT";
        break;
    case GestureDirection::idle:
        stream << "IDLE/NONE";
        break;
    }
    return stream;
}