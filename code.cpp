
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

    //Square grid2D({0, 2}, 1000, {0,2},1000);

    Functions f2([](const Point& p) {
    double x = p[0];
        double y = p[1];
        double z = p[2];
    return Point{1/(std::sqrt(x*x+y*y+z*z))};});

    Polynomial f3({1});
    Circle mycirc({4,4,2}, 2,200,200, 200);

    cout << "Milieu : "
        << Midpoint(mycirc, f2).integrate()[0] << "  "
        << endl;

    cout << "Trapezes : "<< Trapezoidal(mycirc, f2).integrate()[0] << "  "<< endl;

    cout << "Simpson : "
        << Simpson(mycirc, f2).integrate()[0] << "  "
        << endl;

    return 0;
}