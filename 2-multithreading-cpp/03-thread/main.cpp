#include <iostream>
#include <thread>

using namespace std;

void fun(const string& s)
{
    for(int i=0; i<10; i++)
    {
        cout<< s << "\n";
        this_thread::sleep_for(500ms);
    }
}

int main()
{
    thread t(fun, "world");
    fun("hello");
    t.join();
}
