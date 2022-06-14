#include <iostream>
#include <unistd.h>
#include <linux/input.h>
#include <string>
#include "EventHandler.h"
#include "TouchpadInputEventSource.h"

int main(int argc, char *argv[])
{
    TouchpadInputEventSource eventSource;

    try
    {
        EventHandler handler;
        for (;;)
        {
            const input_event& ev = eventSource.getEvent();
            handler.put(ev);
        }
    }
    catch(std::exception& e) {
        std::cerr << e.what();
    }

    return EXIT_SUCCESS;
}
