//
//  Polygon.hpp
//  FirstLab
//
//  Created by Bill Williams on 2/16/21.
//

#ifndef Polygon_hpp
#define Polygon_hpp

#include <stdio.h>
#include "BrokenLine.hpp"
#include "Vector.hpp"
#include <cmath>

class Polygon{
protected:
    ClosedBrokenLine line;
public:
    explicit Polygon(const ClosedBrokenLine& line);
    Polygon() = default;
    Polygon(const Polygon& obj);
    Polygon& operator=(Polygon& obj);
    float perimeter() const;
    virtual float square() const;
    virtual ~Polygon() = default;
};

class Triangle : public Polygon{
public:
    explicit Triangle(const ClosedBrokenLine& line);
    float square() const;
};

class Trapeze : public Polygon{
    
public:
    explicit Trapeze(const ClosedBrokenLine& line);
    float square() const;
};

    class RegularPolygon : public Polygon{
public:
    RegularPolygon(const ClosedBrokenLine& line);
    float square() const;
};
#endif /* Polygon_hpp */
