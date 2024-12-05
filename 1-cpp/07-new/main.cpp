#include <iostream>
#include <string>

using namespace std;

int main()
{
    string onStack("a");
    string *onHeap = new string("b");
    auto *s2 = new string("c");
    cout << onStack << *onHeap << *s2;
    delete onHeap;
    delete s2;
    return 0;
}
