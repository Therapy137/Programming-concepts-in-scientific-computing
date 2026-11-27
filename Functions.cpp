//
// Created by Theo on 26.11.2026.
//

#include "Functions.h"
#include <functional>
#include <math.h>
#include <iostream>
Functions::Functions(std::function<Point(const Point &)> func)
    : f(func) {
}

Point Functions::evaluate(const Point &p) const { return f(p); }

Polynomial::Polynomial( std::initializer_list<double> c)
    : Functions([vec = std::vector<double>(c)](const Point &p) {
        double result = 0.0;
        std::size_t k = 0;
        for (int i = 0; k < vec.size(); ++i) {
            for (int j = 0; j <= i && k < vec.size(); ++j, ++k) {
                result += vec[k] * std::pow(p[0], i) * std::pow(p[1], j);
            }
        }
        return Point{result, 0.0, 0.0};
    })
{
    std::vector<double> vec(c);
    std::size_t k = 0;

    for (int i = 0; k < vec.size(); ++i) {
        for (int j = 0; j <= i && k < vec.size(); ++j, ++k) {
            std::cout << vec[k] << "x^" << i << "y^" << j << " ";
        }
    }
    std::cout << std::endl;
}