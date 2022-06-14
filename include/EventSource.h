#include <linux/input.h>

class EventSource
{
public:
    virtual const input_event& getEvent() = 0;
};
