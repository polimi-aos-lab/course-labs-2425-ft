#include <iostream>

using namespace std;

void fun(int i) { cout << i << "I\n"; }

void fun(double d) { cout << d << "D\n"; }

int main()
{
    fun(42);
    fun(42.5);
    return 0;
}
