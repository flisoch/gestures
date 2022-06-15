#include <iostream>
#include <unistd.h>
#include <linux/input.h>
#include <string>
#include <thread>
#include "ThreadsafeQueue.h"
#include "EventHandler.h"
#include "MT_EventSource.h"

ThreadsafeQueue<std::string> commands;

void mtEvents()
{
    MT_EventSource eventSource;

    try
    {
        EventHandler handler;
        for (;;)
        {
            const input_event &ev = eventSource.getEvent();
            handler.put(ev);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what();
    }
}

void commandExecutor()
{
    std::shared_ptr<std::string> command = commands.waitAndPop();
    if (command != nullptr) {
        system(command->c_str());   
    }
}

int main(int argc, char *argv[])
{

    std::thread t1(mtEvents);
    std::thread t2(commandExecutor);
    t1.join();
    t2.join();
    return EXIT_SUCCESS;
}
