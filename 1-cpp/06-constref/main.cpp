#include <iostream>
#include <string>

using namespace std;

void fun(const string& s) {
	cout << s << "\n";
}

int main() {
	fun("Hello world");
    return 0;
}
