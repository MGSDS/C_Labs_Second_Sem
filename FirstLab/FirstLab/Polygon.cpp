//
//  Polygon.cpp
//  FirstLab
//
//  Created by Bill Williams on 2/16/21.
//

#include "Polygon.hpp"
#include <vector>

//Polygon Class Sectioon

Polygon::Polygon(const ClosedBrokenLine& line): line(line){
    const Point* points = line.getPointArr();
    size_t sz = line.getPointsCount();
    if(sz > 1){
        Vector vectors[sz];
        for(int i = 1; i < sz; ++i)
            vectors[i-1] = Vector(points[i-1], points[i]);
        vectors[sz-1] = Vector(points[sz-1], points[0]);
    
        bool clockwise = false;
        
        if(vectors[0].getX()*vectors[1].getY()-vectors[0].getY()*vectors[1].getX()>0)
            clockwise = true;
        else if (vectors[0].getX()*vectors[1].getY()-vectors[0].getY()*vectors[1].getX() == 0)
            throw std::invalid_argument("Polygon is not convex");
        
        if(clockwise){
            for(int i = 1; i < sz-1; ++i)
                if(vectors[i].getX()*vectors[i + 1].getY()-vectors[i].getY()*vectors[i + 1].getX() <= 0)
                    throw std::invalid_argument("Polygon is not convex");
            if(vectors[sz-1].getX()*vectors[0].getY()-vectors[sz-1].getY()*vectors[0].getX() <= 0)
                throw std::invalid_argument("Polygon is not convex");
        }
        else{
            for(int i = 1; i < sz-1; ++i)
                if(vectors[i].getX()*vectors[i + 1].getY()-vectors[i].getY()*vectors[i + 1].getX() >= 0)
                    throw std::invalid_argument("Polygon is not convex");
            if(vectors[sz-1].getX()*vectors[0].getY()-vectors[sz-1].getY()*vectors[0].getX() >= 0)
                throw std::invalid_argument("Polygon is not convex");
        }
    }
}

Polygon::Polygon(const Polygon& obj){
    this->line = obj.line;
}

float Polygon::perimeter() const{
    return line.length();
}

void* Polygon::operator new[](size_t size){
    void * ptr;
    ptr = malloc(size);
    if (!ptr){
        std::bad_alloc error;
        throw error;
    }
    return ptr;
}

float Polygon::square() const{
    float ans = 0;
    const Point* points = line.getPointArr();
    for (int i = 0; i < line.getPointsCount() - 1; ++i)
        ans += points[i].getX()*points[i+1].getY();
        
    ans += points[line.getPointsCount() - 1].getX()*points[0].getY();
    
    for (int i = 0; i < line.getPointsCount() - 1; ++i)
        ans -= points[i+1].getX()*points[i].getY();
    
    ans -= points[0].getX()*points[line.getPointsCount() - 1].getY();
    
    return abs(ans)/2;
}

void Polygon::operator delete[](void *p){
    free(p);
}

//Triangle Class Section

Triangle::Triangle(const ClosedBrokenLine& line) : Polygon(line){
    if(line.getPointsCount() != 3){
        throw std::invalid_argument("ClosedBrokenLine line is not a triangle");
    }
}

float Triangle::square() const{
    const Point * arr = line.getPointArr();
    return 0.5 * abs((arr[1].getX()-arr[0].getX())*(arr[2].getY()-arr[0].getY())-(arr[1].getY()-arr[0].getY())*(arr[2].getX()-arr[0].getX()));
}

//Trapeze Class Section

Trapeze::Trapeze(const ClosedBrokenLine& line) : Polygon(line){
    size_t n = line.getPointsCount();
    if(n != 4)
        throw std::invalid_argument("ClosedBrokenLine line is not a trapeze: more or less than 4 points");
    const Point * arr = line.getPointArr();
    
    {
        float a = Vector(arr[0], arr[1]).crossProduct(Vector(arr[2], arr[3]));
        float b = Vector(arr[1], arr[2]).crossProduct(Vector(arr[0], arr[3]));
        if((a != 0 && b != 0) || (a == 0 && b == 0))
            throw std::invalid_argument("ClosedBrokenLine line is not a trapeze");
    }
}

float Trapeze::square() const{
    const Point * arr = line.getPointArr();
    float a;
    float b;
    float c;
    float d;
    if(Vector(arr[0], arr[1]).crossProduct(Vector(arr[2], arr[3])) == 0){
        a = Vector(arr[0], arr[1]).length();
        b = Vector(arr[2],arr[3]).length();
        c = Vector(arr[1],arr[2]).length();
        d = Vector(arr[3], arr[0]).length();
    }
    else{
        a = Vector(arr[1], arr[2]).length();
        b = Vector(arr[3],arr[0]).length();
        c = Vector(arr[0],arr[1]).length();
        d = Vector(arr[2], arr[3]).length();
    }
    float square;
    if(a > b)
        square = ((a+b)/2)*sqrt(pow(c, 2)-pow((pow(a-b,2)+pow(c,2)-pow(d,2))/(2*(a-b)), 2));
    else
        square = ((b+a)/2)*sqrt(pow(c, 2)-pow((pow(b-a,2)+pow(c,2)-pow(d,2))/(2*(b-a)), 2));
    return  square;
}

//RegularPolygon Class Section

RegularPolygon::RegularPolygon(const ClosedBrokenLine& line) : Polygon(line){
    std::vector<float> angles;
    std::vector<float> len;
    std::vector<Vector> vectors;
    const Point * arr = line.getPointArr();
    size_t n = line.getPointsCount();
    for(auto i = 0; i < n-1; ++i){
        Vector vec = Vector(arr[i], arr[i+1]);
        vectors.push_back(vec);
        len.push_back(vectors[i].length());
    }
    vectors.push_back(Vector(arr[n-1], arr[0]));
    len.push_back(vectors[n-1].length());
    for(int i = 0; i < vectors.size()-1; ++i){
        angles.push_back(vectors[i].cosAngle(vectors[i+1]));
    }
    angles.push_back(vectors[vectors.size()-1].cosAngle(vectors[0]));
    for (auto i = angles.begin()+1; i < angles.end(); ++i) {
        if(*i != *(i-1))
            throw std::invalid_argument("ClosedBrokenLine line is not a regular polygon");
    }
    for (auto i = len.begin()+1; i < len.end(); ++i) {
        if(*i != *(i-1))
            throw std::invalid_argument("ClosedBrokenLine line is not a regular polygon");
    }
    
}

float RegularPolygon::square() const{
    return (line.getPointsCount()*pow(Vector(line.getPointArr()[0], line.getPointArr()[1]).length(), 2))/(4*tan((360/(2*line.getPointsCount()))*(M_PI/180)));
}
