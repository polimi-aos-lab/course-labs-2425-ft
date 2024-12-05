#pragma once

#include <iostream>

class Foo {
public:
    Foo()
    {
        ptr = new int;
        std::cout << "Constructor called\n";
    }
    
    ~Foo()
    {
        delete ptr;
        std::cout << "Destructor called\n";
    }
    
    //Make class noncopyable
    Foo(const Foo&) = delete;
    Foo& operator=(const Foo&) = delete;

private:
    int *ptr;
};
