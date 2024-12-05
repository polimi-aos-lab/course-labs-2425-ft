#include <stdio.h>
#include "point.h"

void Point::print() const
{
    printf("x=%d y=%d\n", this->x, this->y);
}
