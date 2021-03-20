//
//  main.cpp
//  FirstLab
//
//  Created by Bill Williams on 2/16/21.
//

#include <iostream>
#include "Polygon.hpp"

int main(int argc, const char * argv[]) {
    
    //Trapeze
    
    Point * points = new Point[4];
    points[0] = Point(4,1); points[1] = Point(7,1); points[2] = Point(1,13); points[3] = Point(1,7);
    ClosedBrokenLine linetrap (points, 4);
    Trapeze trap(linetrap);
    
    //Triangle
    
    points[0] = Point(1,9); points[1] = Point(1,14); points[2] = Point(6,10);
    ClosedBrokenLine linetri (points, 3);
    Triangle triangle(linetri);
    
    //Regular polygon
    
    points[0] = Point(8, 8); points[1] = Point(12,8); points[2] = Point(12,12); points[3] = Point(8,12);
    ClosedBrokenLine linesq (points, 4);
    RegularPolygon square (linesq);
    
    //array
    
    Polygon t(linesq);
    
    std::cout << t.square() << '\n';
    
    Polygon ** arr = new Polygon*[3];
    arr[0] = &trap; arr[1]= &triangle; arr[2] = &square;

    std::cout << "Trapeze\n";
    std::cout << "Perimeter: " << arr[0]->perimeter() << "\nSquare: " << arr[0]->square();
    std::cout << "\nTriangle\n";
    std::cout << "Perimeter: " << arr[1]->perimeter() << "\nSquare: " << arr[1]->square();
    std::cout << "\nRegular polygon\n";
    std::cout << "Perimeter: " << arr[2]->perimeter() << "\nSquare: " << arr[2]->square();
    
    std::cout << '\n';

    return 0;
}
