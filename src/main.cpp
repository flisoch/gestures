#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include "EventHandler.cpp"

#define EVENT_DEVICE "/dev/input/event4"
#define EVENT_TYPE EV_ABS
#define EVENT_CODE_X ABS_X
#define EVENT_CODE_Y ABS_Y

/* TODO: Close fd on SIGINT (Ctrl-C), if it's open */

using namespace std;
void print_device_name(int fd)
{
    char name[256] = "Unknown";
    ioctl(fd, EVIOCGNAME(sizeof(name)), name);
    printf("Reading from:\n");
    printf("device file = %s\n", EVENT_DEVICE);
    printf("device name = %s\n", name);
}

int main(int argc, char *argv[])
{
    struct input_event ev;
    int fd;

    /* Open Device */
    fd = open(EVENT_DEVICE, O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "%s is not a vaild device\n", EVENT_DEVICE);
        return EXIT_FAILURE;
    }

    /* Print Device Name */
    print_device_name(fd);

    EventHandler handler = EventHandler();
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

    return EXIT_SUCCESS;
err:
    close(fd);
    return EXIT_FAILURE;
}
