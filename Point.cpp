//
// Created by Theo on 26.11.2026.
//

#include "Point.h"
#include <stdexcept>

Point::Point(std::initializer_list<double> values) : p(values) {
};
double Point::operator[](std::size_t i) const {
    return p.at(i);
};

Point Point::operator+(const Point &other) const {
    if (p.size() != other.p.size())
        throw std::invalid_argument("Dimensions incompatibles");
    Point result = *this;
    for (std::size_t i = 0; i < p.size(); i++)
        result.p[i] += other.p[i];
    return result;
}

Point Point::operator-(const Point &other) const {
    if (p.size() != other.p.size())
        throw std::invalid_argument("Dimensions incompatibles");
    Point result = *this;
    for (size_t i = 0; i < p.size(); i++)
        result.p[i] -= other.p[i];
    return result;
}

Point Point::operator*(double scalar) const {
    Point result = *this;
    for (size_t i = 0; i < p.size(); i++)
        result.p[i] *= scalar;
    return result;
};

std::size_t Point::dimension() const {
    return p.size();
};
