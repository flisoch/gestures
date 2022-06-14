#include "TouchpadInputEventSource.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

TouchpadInputEventSource::TouchpadInputEventSource()
{
    event_device_path = findEventDevicePath();
    // todo: throw exception if fd==-1
    device_fd = open(event_device_path.c_str(), O_RDONLY);
    printDeviceName();
}

TouchpadInputEventSource::~TouchpadInputEventSource()
{
    close(device_fd);
}

std::string TouchpadInputEventSource::findEventDevicePath()
{
    FILE *pipe_stream = popen("cat /proc/bus/input/devices  | grep -P '^[NH]: ' | grep -A1 Touchpad | grep -o 'event\\w*'", "r");
    char event_name[128];
    fgets(event_name, sizeof event_name, pipe_stream);
    pclose(pipe_stream);
    std::string event_device_path = "/dev/input/" + std::string(event_name);
    event_device_path.pop_back(); // remove last character to open correct device
    return event_device_path;
}

void TouchpadInputEventSource::printDeviceName()
{
    // todo: check if fd and device are initialized
    char name[256] = "Unknown";
    ioctl(device_fd, EVIOCGNAME(sizeof(name)), name);
    printf("Reading from:\n");
    printf("device file = %s\n", event_device_path.c_str());
    printf("device name = %s\n", name);
}

const input_event &TouchpadInputEventSource::getEvent()
{
    const size_t ev_size = sizeof(struct input_event);
    ssize_t size;

    size = read(device_fd, &ev, ev_size);
    if (size < ev_size)
    {
        std::cerr << "Error size when reading\n";
    }
    return ev;
}
