#include<math.h>
#ifndef COORDINATE_H
#define COORDINATE_H

struct Coordinate{
    double x;
    double y;
};

double distance(Coordinate c1, Coordinate c2);

#endif