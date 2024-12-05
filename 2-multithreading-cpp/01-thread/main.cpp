#include <iostream>
#include <thread>

using namespace std;

void myThread()
{
    for(;;)
    {
        cout<<"world \n";
        this_thread::sleep_for(500ms);
    }
}
int main()
{
    thread t(myThread);
    for(;;)
    {
        cout<<"Hello\n";
        this_thread::sleep_for(500ms);
    }
}
