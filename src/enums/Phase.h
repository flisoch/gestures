#ifndef __PHASE_H__
#define __PHASE_H__

#include <iostream>

enum class Phase
{
    start,
    update,
    end,
    idle
};

inline std::ostream &operator<<(std::ostream &stream, const Phase phase)
{
    switch (phase)
    {
    case Phase::start:
        stream << "START";
        break;
    case Phase::update:
        stream << "UPDATE";
        break;
    case Phase::end:
        stream << "END";
        break;
    case Phase::idle:
        stream << "IDLE/NONE";
        break;
    }
    return stream;
}
#endif // __PHASE_H__