#ifndef __TOUCHPADINPUTEVENTSOURCE_H__
#define __TOUCHPADINPUTEVENTSOURCE_H__

#include "EventSource.h"
#include <string>

class TouchpadInputEventSource : public EventSource
{
public:
    TouchpadInputEventSource();
    ~TouchpadInputEventSource();

    const input_event &getEvent() override;

private:
    std::string findEventDevicePath();
    void printDeviceName();

    int device_fd;
    std::string event_device_path;
    struct input_event ev;
};
#endif // __TOUCHPADINPUTEVENTSOURCE_H__
