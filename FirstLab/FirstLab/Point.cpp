//
//  Point.cpp
//  FirstLab
//
//  Created by Bill Williams on 2/16/21.
//

#include "Point.hpp"


Point::Point(const Point& obj){
    x = obj.x;
    y = obj.y;
}

Point& Point::operator= (const Point& obj){
    x = obj.x;
    y = obj.y;
    return * this;
}

float Point::distanceTo(Point& obj){
    return sqrt(pow(Point::x-obj.getY(), 2) + pow(Point::y-obj.getY(),2));
}

