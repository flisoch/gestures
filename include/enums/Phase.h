#ifndef __PHASE_H__
#define __PHASE_H__

#include <iostream>

enum class Phase
{
    start,
    update,
    end,
    undefined
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
    case Phase::undefined:
        stream << "IDLE/NONE";
        break;
    }
    return stream;
}

inline std::string to_string(const Phase phase) {
  switch (phase) {
    case Phase::start:   return "start";
    case Phase::update: return "update";
    case Phase::end:  return "end";
    case Phase::undefined: return "undefined";
    default: return "undefined";
  }
}

#endif // __PHASE_H__
