#include <iostream>
#include <thread>

using namespace std;

void fun(const string& s)
{
    for(;;)
    {
        cout << s << "\n";
        this_thread::sleep_for(500ms);
    }
}
int main()
{
    thread t(fun, "world");
    fun("hello");
}
