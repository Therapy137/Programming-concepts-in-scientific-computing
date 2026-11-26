//
// Created by Theo on 26.11.2026.
//

#ifndef MYPROJECT_FUNCTIONS_H
#define MYPROJECT_FUNCTIONS_H
#include "Point.h"
#include <functional>

class Functions {
private:
    std::function<Point(const Point&)> f;
public:
    Functions(std::function<Point(const Point &)> func);
    Point evaluate(const Point &p) const;
};


#endif //MYPROJECT_FUNCTIONS_H
