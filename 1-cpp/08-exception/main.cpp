#include <iostream>
#include <stdexcept>

void foo(int i) {
	if(i < 0) throw std::logic_error("i<0");
}

void bar(int i) {
	foo(i);
}

int main()
{
    try {
		bar(-2);
	} catch(std::exception& e) {
		std::cout << e.what() << "\n";
	}
}
