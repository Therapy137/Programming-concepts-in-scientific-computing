//
// Created by Theo on 26.11.2026.
//

#ifndef MYPROJECT_FUNCTIONS_H
#define MYPROJECT_FUNCTIONS_H
#include "Point.h"
#include <vector>
#include <functional>

class Functions {
protected:
    std::function<Point(const Point&)> f;
public:
    Functions() = default;
    virtual ~Functions() = default;

    Functions(std::function<Point(const Point &)> func);
    Point evaluate(const Point &p) const;
};
class Polynomial : public Functions {
public:
    Polynomial(std::initializer_list<double> c);
};

#endif //MYPROJECT_FUNCTIONS_H
