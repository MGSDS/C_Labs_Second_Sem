//
//  Point.hpp
//  FirstLab
//
//  Created by Bill Williams on 2/16/21.
//

#ifndef Point_hpp
#define Point_hpp

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <new>

class Point {
private:
    float x;
    float y;
public:
    explicit Point(float x = 0, float y = 0) : x(x), y(y){}
//    bool operator==(const point& obj);
    Point(const Point& obj);
    Point& operator= (const Point& obj);
    float distanceTo(Point& obj);
    float getX() const{ return x; }
    float getY() const{ return y; }
};

#endif /* Point_hpp */
