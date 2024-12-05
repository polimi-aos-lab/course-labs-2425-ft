#include <iostream>

using namespace std;

int main() {
    int i = 0;
    
    //Capture by value (copy)
    auto myLambda1 = [=](int j) {
        cout << i << j << "\n";
    };

    //Call lambda function
    myLambda1(10);
}
