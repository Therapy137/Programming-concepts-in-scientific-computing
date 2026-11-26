
#include <iostream>
#include <iomanip>
#include <cmath>
#include "Point.h"
#include "Grid.h"
#include "Functions.h"
#include "Integration.h"
using namespace std;



int main() {

    cout << fixed << setprecision(8);

    Grid grid2D({0, 2}, 1000, {0,2},1000);

    Functions f2([](const Point& p) {
    double x = p[0];
        double y = p[1];
    return Point{exp(-x*x-y*y)};});

    cout << "\nTest R^2 -> R^3 :" << endl;
    Polynomial f3({1,2,3,1,4,2});
    cout << "Milieu : "
        << Midpoint(grid2D, f3).integrate()[0] << "  "
        << endl;

    cout << "Trapezes : "
        << Trapezoidal(grid2D, f3).integrate()[0] << "  "
        << endl;

    cout << "Simpson : "
        << Simpson(grid2D, f2).integrate()[0] << "  "
        << endl;

    return 0;
}