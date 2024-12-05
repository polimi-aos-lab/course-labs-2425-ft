//Don't write code like this

#include <iostream>
#include <thread>

using namespace std;

static volatile int sharedVariable=0;

void fun()
{
    for(int i=0;i<1000000;i++) sharedVariable++;
}

int main()
{
    thread t(fun);
    for(int i=0;i<1000000;i++) sharedVariable--;
    t.join();
    cout<<"sharedVariable="<<sharedVariable<<"\n";
}
