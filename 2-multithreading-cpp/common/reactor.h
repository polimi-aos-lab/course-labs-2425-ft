#pragma once

#include <functional>
#include "synchronized_queue.h"
#include "active_object.h"

class Reactor: public ActiveObject
{
public:
    void pushTask(std::function<void ()> func);

    virtual ~Reactor();

private:
    virtual void run();

    SynchronizedQueue<std::function<void ()>> tasks;
};
