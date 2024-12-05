//Don't write code like this

#pragma once

#include <list>
#include <mutex>
#include <condition_variable>

template<typename T>
class SynchronizedQueue
{
public:
    SynchronizedQueue() {}
    
    void put(const T & data);
    
    T get();

private:
    SynchronizedQueue(const SynchronizedQueue &)=delete;
    SynchronizedQueue & operator=(const SynchronizedQueue &)=delete;
    
    std::list<T> queue;
    std::mutex myMutex;
};

template<typename T>
void SynchronizedQueue<T>::put(const T& data)
{
    std::unique_lock<std::mutex> lck(myMutex);
    queue.push_back(data);
}

template<typename T>
T SynchronizedQueue<T>::get()
{
    for(;;)
    {
        std::unique_lock<std::mutex> lck(myMutex);
        if(queue.empty()) continue;
        T result=queue.front();
        queue.pop_front();
        return result;
    }
}
