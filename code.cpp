
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

    Grid grid2D({-100, 100}, 1000, {-100,100},1000);

    Functions f2([](const Point& p) {
    double x = p[0];
        double y = p[1];
    return Point{exp(-x*x-y*y)};});

    Midpoint I1(grid2D, f2);
    Trapezoidal I2(grid2D, f2);
    Simpson I3(grid2D, f2);


    cout << "\nTest R^2 -> R^3 :" << endl;

    cout << "Milieu : "
        << I1.integrate()[0] << "  "
        << endl;

    cout << "Trapezes : "
        << I2.integrate()[0] << "  "
        << endl;

    cout << "Simpson : "
        << I3.integrate()[0] << "  "
        << endl;

    return 0;
}