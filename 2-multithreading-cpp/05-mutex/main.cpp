
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

static volatile int sharedVariable=0;
mutex myMutex;

void fun()
{
    for(int i=0;i<1000000;i++)
    {
        myMutex.lock();
        sharedVariable++;
        myMutex.unlock();
    }
}

int main()
{
    thread t(fun);
    for(int i=0;i<1000000;i++)
    {
        myMutex.lock();
        sharedVariable--;
        myMutex.unlock();
    }
    t.join();
    cout<<"sharedVariable="<<sharedVariable<<"\n";
}
