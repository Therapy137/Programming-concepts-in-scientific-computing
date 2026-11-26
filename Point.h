//
// Created by Theo on 26.11.2026.
//

#ifndef MYPROJECT_POINT_H
#define MYPROJECT_POINT_H
#include <initializer_list>
#include <vector>

class Point {
private:
    std::vector<double> p;
public:
    double operator[](std::size_t i) const;
    Point(std::initializer_list<double> values);
    Point operator+(const Point &other) const;
    Point operator-(const Point &other) const;
    Point operator*(double scalar) const;
    std::size_t dimension() const;

};


#endif //MYPROJECT_POINT_H
