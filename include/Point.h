#include <string>
#include <random>
#include "Coordinate.h"

#ifndef POINT_H
#define POINT_H



class Point{
    private:
        // name of the meeting point
        std::string _name;
        // coordinate
        Coordinate _position;
        // probability for people to go here
        double _prob;
        // when the distance of position of the person 
        // and fixed point <= the radius, it is defined that the person
        // has approached the point
        double _approchradius;

    public:
        // Constructor
        Point();
        Point(std::string name, Coordinate position, double approachradius);
        std::string name();
        Coordinate position();
        double approachradius();

        Point& operator=(const Point& from_Community);
};

static Point point_null = Point();


#endif