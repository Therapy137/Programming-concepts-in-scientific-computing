//
// Created by Theo on 26.11.2026.
//

#include "Functions.h"
#include <functional>

Functions::Functions(std::function<Point(const Point &)> func)
    : f(func) {
}

Point Functions::evaluate(const Point &p) const { return f(p); }
