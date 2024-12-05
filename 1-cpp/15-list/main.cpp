#include <list>
#include "point.h"

using namespace std;

int main()
{
    list<Point2D> pts;
    //Insertion
    pts.push_front(Point2D(1,2));
    pts.push_back(Point2D(3,4));
    //Iteration
	for(auto& p : pts) p.print();
    //Front/back access
    auto p1 = pts.front();
    auto p2 = pts.back();
    //Front/back removal
    pts.pop_front();
	pts.pop_back();
}
