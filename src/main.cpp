#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string>
#include "EventHandler.h"
#include "libconfig.h++"

#define EVENT_DEVICE "/dev/input/event12"
#define EVENT_TYPE EV_ABS
#define EVENT_CODE_X ABS_X
#define EVENT_CODE_Y ABS_Y

std::string get_mt_event_device()
{
    // find device event
    FILE *output_file = popen("cat /proc/bus/input/devices  | grep -P '^[NH]: ' | grep -A1 Touchpad | grep -o 'event\\w*'", "r");
    char buffer[128];
    fgets(buffer, sizeof buffer, output_file);
    pclose(output_file);
    std::string device = "/dev/input/";
    device += std::string(buffer);
    device.pop_back(); // remove last character to open correct device
    return device;
}

void print_device_name(int fd, const std::string &event_device)
{
    char name[256] = "Unknown";
    ioctl(fd, EVIOCGNAME(sizeof(name)), name);
    printf("Reading from:\n");
    printf("device file = %s\n", event_device.c_str());
    printf("device name = %s\n", name);
}

int main(int argc, char *argv[])
{
    struct input_event ev;
    int fd;
    std::string event_device = get_mt_event_device();

    /* Open Device */
    fd = open(event_device.c_str(), O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "%s is not a vaild device\n", event_device.c_str());
        return EXIT_FAILURE;
    }

    /* Print Device Name */
    print_device_name(fd, event_device);

    try
    {
        EventHandler handler;
        for (;;)
        {
            const size_t ev_size = sizeof(struct input_event);
            ssize_t size;

            /* TODO: use select() */

            size = read(fd, &ev, ev_size);
            if (size < ev_size)
            {
                fprintf(stderr, "Error size when reading\n");
                goto err;
            }
            handler.put(ev);
        }
    }
    catch(std::exception& e) {
        std::cerr << e.what();
    }

    return EXIT_SUCCESS;
err:
    close(fd);
    return EXIT_FAILURE;
}
