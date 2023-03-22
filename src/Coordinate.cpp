#include "Coordinate.h"

double distance(Coordinate c1, Coordinate c2){
    double distance = (c1.x - c2.x)*(c1.x - c2.x) + (c1.y - c2.y)*(c1.y - c2.y);
    //double distance = pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2);
    //double distance = sqrt(pow(c1.x - c2.x,2) + pow(c1.y - c2.y,2));
    return distance;
}