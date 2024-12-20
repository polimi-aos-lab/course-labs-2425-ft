
#include "synchronized_queue_bad.h"
#include <iostream>
#include <thread>

using namespace std;

SynchronizedQueue<int> queue;

void myThread()
{
    for(;;) cout << queue.get() << "\n";
}

int main()
{
    thread t(myThread);
    for(int i=0;;i++)
    {
        queue.put(i);
        this_thread::sleep_for(1s);
    }
}
