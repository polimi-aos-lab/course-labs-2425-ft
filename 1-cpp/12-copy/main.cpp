#include "foo.h"

int main()
{
    Foo foo;
    Foo foo2(foo);
    foo=foo2;
} //Destructor called here
