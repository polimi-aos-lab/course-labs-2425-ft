#include <iostream>
#include <string>
#include <cstdio>

int main()
{
    std::string s = "Hello";
    s += " world";
    s.at(6) = 'W';
    std::cout << s.length() << "\n";
    std::cout << s << "\n";
    printf("%s\n", s.c_str());
    return 0;
}
