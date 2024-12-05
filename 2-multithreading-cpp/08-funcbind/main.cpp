#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;

void printAdd(int a, int b)
{
    cout << a << '+' << b << '=' << a + b << "\n";
}

int main()
{
    function<void ()> func;
    func = bind(&printAdd, 2, 3);
    func();
}
