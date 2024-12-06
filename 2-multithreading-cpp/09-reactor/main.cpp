#include <iostream>
#include <chrono>
#include "../common/reactor.h"

using namespace std;

void printAdd(int a, int b)
{
    this_thread::sleep_for(5s);
    cout << a << '+' << b << '=' << a + b << "\n";
}

int main()
{
    Reactor reac;
    int a,b;
    while(cin >> a >> b) reac.pushTask([=](){ printAdd(a,b); });
}
