#include <stdio.h>
#include "point.h"

void Point2D::print() const
{
    printf("x=%d y=%d\n", x, y);
}

void Point3D::print() const
{
    printf("x=%d y=%d z=%d\n", x, y, z);
}
