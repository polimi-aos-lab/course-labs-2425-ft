#include <iostream>
#include "point.h"

using namespace std;

int main()
{
    Point3D point(10,15,7);
    //point.print(); //Need polymorphism to be able to print z too
    cout << "x=" << point.getX()
         << " y=" << point.getY()
         << " z=" << point.getZ() << "\n";
}
