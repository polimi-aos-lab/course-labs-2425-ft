#include <iostream>
#include "point.h"

using namespace std;

void fun(const Point& p) { 
    p.print();
}

int main() {
    Point2D p1(10,20);
    Point3D p2(10,20,30);
    fun(p1);
    fun(p2);
}
