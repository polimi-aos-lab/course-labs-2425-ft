#include <memory>
#include "point.h"

using namespace std;

int main()
{
    //Construct shared_ptr (two ways)
    //1st is a shared_ptr<Point>
    //2nd is a shared_ptr<Point2D>
    shared_ptr<Point> p(new Point2D(1,2));
    auto p2=make_shared<Point2D>(1,2);
    //Use them like pointers
	p->print();
    p2->print();
    //Shared ownership of the
    //pointed-to object
    shared_ptr<Point> p3;
    p3=p2;
    p3=p;
    //Delete automatically called
    //when last shared_ptr out of scope 
}
