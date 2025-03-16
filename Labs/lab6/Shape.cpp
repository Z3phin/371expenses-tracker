#include "Shape.h"
#include <sstream>
#include <cmath>

Shape::Shape() {}
Shape::~Shape() {}

Circle::Circle(const double _x, const double _y, const double _r)
    : Shape(), x(x), y(y), r(r) {}

Circle::~Circle() {}

std::string Circle::to_string() const {
    std::stringstream ss;
    ss << "Circle centred at (" << x << ", " << y << ") with radius " << r << "...";
    return ss.str();            
}

void Circle::centre_at(double newX, double newY) {
    this->x = newX;
    this->y = newY; 
}

Rectangle::Rectangle(const double _x0, const double _y0, 
                     const double _x1, const double _y1)
        : Shape(), x0(_x0), y0(_y0), x1(_x1), y1(_y1) {}

Rectangle::~Rectangle() {}

std::string Rectangle::to_string() const {
    const double width = x0 - x1;
    const double height = y0 - y1; 

    std::stringstream ss;
    ss << "Rectangle at [(" << x0 << ", " << y0 
       << "), (" << x1 << ", " << y1 
       << ")] with width " << width 
       <<", height " << height <<"...";
    return ss.str();
} 

void Rectangle::centre_at(const double x, const double y) {
    const double width = x0 - x1;
    const double height = y0 - y1; 

    this->x0 = x + (width / 2.0);
    this->x1 = x - (width / 2.0);
    this->y0 = y + (height / 2.0);
    this->y1 = y + (height / 2.0);
}

Triangle::Triangle(const double _x0, const double _y0, 
                   const double _x1, const double _y1,
                   const double _x2, const double _y2) 
        : Shape(), x0(_x0), y0(_y0), x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}

Triangle::~Triangle() {}

std::string Triangle::to_string() const {
    const double length1 = sqrt(pow(x1-x0, 2) + pow(y1-y0, 2));
    const double length2 = sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
    const double length3 = sqrt(pow(x0-x2, 2) + pow(y0-y2, 2));

    std::stringstream ss;
    ss << "Triangle at ["
       << "(" << x0 << ", " << y0 <<"),"
       << " (" << x1 << ", " << y1 << "),"
       << " (" << x2 << ", " << y2 << ")"
       << "] with side lengths " << length1 << ", " << length2 << ", and " << length3 << "...";
    return ss.str();
}

void Triangle::centre_at(const double x, const double y) {
    const double curX = (x0 + x1 + x2) / 3.0;
    const double curY = (y0 + y1 + y2) / 3.0;
    
    const double translationX = curX - x; 
    const double translationY = curY - y; 

    this->x0 += translationX; 
    this->x1 += translationX;
    this->x2 += translationX;
    this->y0 += translationY;
    this->y1 += translationY;
    this->y2 += translationY;
}