//
// Created by Theo on 26.11.2026.
//

#include "Functions.h"
#include <functional>
#include <math.h>
Functions::Functions(std::function<Point(const Point &)> func)
    : f(func) {
}

Point Functions::evaluate(const Point &p) const { return f(p); }

Polynomial::Polynomial(std::initializer_list<double> c) : Functions([vec = std::vector<double>(c)](const Point &p) {
    double result = 0.0;
    std::size_t k = 0;
    for (int d = 0; k < vec.size(); ++d) {
        for (int j = 0; j <= d && j< vec.size(); ++j,++k) {
            result += vec[k] * std::pow(p[0], d-j) * std::pow(p[1], j);
        }
    }
    return Point{result};
}){
}
