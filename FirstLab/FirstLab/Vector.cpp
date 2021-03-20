//
//  Vector.cpp
//  FirstLab
//
//  Created by Bill Williams on 2/17/21.
//

#include "Vector.hpp"

Vector::Vector(const Point& a, const Point& b) : x(b.getX()-a.getX()), y(b.getY()-a.getY()){
    setLength(a, b);
}

Vector::Vector(const Vector& obj){
    this->x = obj.x;
    this->y = obj.y;
    this->length_ = obj.length_;
}

Vector& Vector::operator=(const Vector& obj){
    this->x = obj.x;
    this->y = obj.y;
    this->length_ = obj.length_;
    return *this;
}

void Vector::setLength(const Point& a, const Point& b){
    float x = a.getX()-b.getX();
    float y = a.getY()-b.getY();
    this->length_ = sqrt(pow(x,2)+pow(y, 2));
}

float Vector::length() const{
    return length_;
}

float Vector::dotProduct(const Vector& vec){
    return this->x*vec.x + this->y*vec.y;
}

float Vector::cosAngle(Vector &vec){
    return abs(this->dotProduct(vec))/(this->length()*vec.length());
}


float Vector::crossProduct(const Vector& vec){
    return this->x*vec.y - this->y*vec.x;
}

bool Vector::operator==(const Vector& obj) const{
    return (this->x == obj.x) && (this->y == obj.y);
}

