//
//  Vector.hpp
//  FirstLab
//
//  Created by Bill Williams on 2/17/21.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <stdio.h>
#include "Point.hpp"
#include <cmath>

class Vector {
    float x;
    float y;
    float length_;
public:
    Vector(const Point& a, const Point& b);
    explicit Vector(float x = 0, float y = 0, float length = 0) : x(x), y(y), length_(length){}
    Vector(const Vector& obj);
    Vector& operator=(const Vector& obj);
    bool operator==(const Vector& obj) const;
    float dotProduct(const Vector& vec);
    float crossProduct(const Vector& vec);
    float cosAngle(Vector& vec);
    float length() const;
    float getX() const{return x; }
    float getY() const{return y; }
    
private:
    void setLength(const Point& a, const Point& b);
};

#endif /* Vector_hpp */
