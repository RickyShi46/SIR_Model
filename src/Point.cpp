#include"Point.h"
Point::Point(){
    _name = "null";
    _position.x = 0.0;
    _position.y = 0.0;
    _prob = 0.0;
    _approch_radius = 0.0;
}

Point::Point(std::string name, Coordinate position, double approachradius){
    _name = name;
    _position = position;
    _prob = rand() % 10 / 10.0;
    _approch_radius = approachradius;
}

std::string Point::name(){
    return _name;
}

Coordinate Point::position(){
    return _position;
}

double Point::approach_radius(){
    return _approch_radius;
}

Point& Point::operator=(const Point& from_Point){
    _name = from_Point._name;
    _position = from_Point._position;
    _prob = from_Point._prob;
    _approch_radius = from_Point._approch_radius;
    return *this;
}

bool Point::operator==(const Point& from_Point){
    if(_name.compare(from_Point._name) == 0){
        return true;
    }
    else{
        return false;
    }
}