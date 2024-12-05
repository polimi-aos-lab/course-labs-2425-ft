#pragma once

#include <atomic>
#include <thread>

class ActiveObject
{
public:
    ActiveObject();
    
    virtual ~ActiveObject();
    
private:
    virtual void run()=0;
    
    ActiveObject(const ActiveObject &)=delete;
    ActiveObject& operator=(const ActiveObject &)=delete;
protected:
    std::atomic<bool> quit;
    std::thread t;
};
