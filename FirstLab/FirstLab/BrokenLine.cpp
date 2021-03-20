//
//  BrokenLine.cpp
//  FirstLab
//
//  Created by Bill Williams on 2/16/21.
//

#include "BrokenLine.hpp"

//Broken Line Section

BrokenLine::BrokenLine(Point* points, size_t n) : n(n){
    this->points = new Point[n];
    for (int i = 0; i < n; ++i) {
        this->points[i] = points[i];
    }
}

BrokenLine::BrokenLine(const BrokenLine& obj){
//    if(this == &obj)
//        throw std::invalid_argument("Can not assign BrokenLine to itselfe");
    this->n = obj.n;
    points = new Point[this->n];
    for (int i = 0; i < this->n; ++i) {
        this->points[i] = obj.points[i];
    }
}

BrokenLine& BrokenLine::operator= (const BrokenLine& obj){
    Point * tmp = new Point[obj.n];
    for (int i = 0; i < obj.n; ++i) {
        tmp[i] = obj.points[i];
    }
    delete [] this->points;
    this->points = tmp;
    this->n = obj.n;
    
    return * this;
}

float BrokenLine::length() const{
    float tmp = 0;
    for (int i = 0; i < n - 1; ++i){
        tmp += points[i].distanceTo(points[i+1]);
    }
    return tmp;
}

BrokenLine::~BrokenLine(){
    delete [] points;
}

//Closed Broken Line Section

ClosedBrokenLine::ClosedBrokenLine(Point * points, size_t n) : BrokenLine(points, n){}

float ClosedBrokenLine::length() const {
    float tmp = 0;
    for (int i = 0; i < n - 1; ++i){
        tmp += points[i].distanceTo(points[i+1]);
    }
    tmp += points[n-1].distanceTo(points[0]);
    return tmp;
}

ClosedBrokenLine::ClosedBrokenLine() : BrokenLine(nullptr, 0){}
