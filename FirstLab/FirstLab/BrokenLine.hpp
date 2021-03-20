//
//  BrokenLine.hpp
//  FirstLab
//
//  Created by Bill Williams on 2/16/21.
//

#ifndef BrokenLine_hpp
#define BrokenLine_hpp

#include <stdio.h>
#include "Point.hpp"

class BrokenLine {
protected:
    Point* points;
    size_t n;
public:
    BrokenLine(Point* points, size_t n);
    BrokenLine(const BrokenLine& obj);
    BrokenLine& operator= (const BrokenLine& obj);
    virtual ~BrokenLine();
    virtual float length() const;
    const Point* getPointArr() const { return points; };
    size_t getPointsCount() const { return n; };
};

class ClosedBrokenLine : public BrokenLine {
    friend class Polygon;
protected:
    ClosedBrokenLine();
public:
    ClosedBrokenLine(Point * point, size_t n);
    float length() const override;
};

#endif /* BrokenLine_hpp */
