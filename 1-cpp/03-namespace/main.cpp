#include <iostream>

using namespace std;

void fun() { cout << "fun 1\n"; }

namespace n1 {
void fun() { cout << "fun 2\n"; }
}

int main()
{
    fun();
    n1::fun();
    return 0;
}
