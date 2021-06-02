#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include "EventHandler.cpp"

#define EVENT_DEVICE "/dev/input/event12"
#define EVENT_TYPE EV_ABS
#define EVENT_CODE_X ABS_X
#define EVENT_CODE_Y ABS_Y

#define DEBOUNCE = 0.04
#define THRESHOLD_SQUARED = 30

/* TODO: Close fd on SIGINT (Ctrl-C), if it's open */

using namespace std;
int main(int argc, char *argv[])
{
    struct input_event ev;
    int fd;
    char name[256] = "Unknown";

    // if ((getuid ()) != 0) {
    //     fprintf(stderr, "You are not root! This may not work...\n");
    //     return EXIT_SUCCESS;
    // }

    /* Open Device */
    fd = open(EVENT_DEVICE, O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "%s is not a vaild device\n", EVENT_DEVICE);
        return EXIT_FAILURE;
    }

    /* Print Device Name */
    ioctl(fd, EVIOCGNAME(sizeof(name)), name);
    printf("Reading from:\n");
    printf("device file = %s\n", EVENT_DEVICE);
    printf("device name = %s\n", name);

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

        if (ev.type == EVENT_TYPE && (ev.code == EVENT_CODE_X || ev.code == EVENT_CODE_Y))
        {
            /* TODO: convert value to pixels */

            if (ev.code == EVENT_CODE_X && ev.value < 100)
            {
                printf("%s = %d\n", ev.code == EVENT_CODE_X ? "X" : "Y",
                       ev.value);
                system("xte \'key XF86MonBrightnessUp\'");
            }
            if (ev.code == EVENT_CODE_X && ev.value > 1120)
            {
                printf("%s = %d\n", ev.code == EVENT_CODE_X ? "X" : "Y",
                       ev.value);
                system("xte \'key XF86MonBrightnessDown\'");
            }
        }
    }

    return EXIT_SUCCESS;

err:
    close(fd);
    return EXIT_FAILURE;
}