//
// Created by Theo on 26.11.2026.
//

#include "Integration.h"
#include <stdexcept>

// Constructeur
Integration::Integration(const Grid &g, const Functions &f)
    : grid(g), func(f) {
}


// Méthode du point milieu
Point Midpoint::integrate() const {
    size_t nx = grid.getNx();
    size_t ny = (grid.getDimension() >= 2) ? grid.getNy() : 1;
    size_t nz = (grid.getDimension() >= 3) ? grid.getNz() : 1;
    Point sum = func.evaluate(grid.getCellCenter(0, 0, 0));
    sum = sum * 0.0;
    for (size_t k = 0; k < nz; k++) {
        for (size_t j = 0; j < ny; j++) {
            for (size_t i = 0; i < nx; i++) {
                Point center = grid.getCellCenter(i, j, k);
                sum = sum + func.evaluate(center);
            }
        }
    }
    return sum * grid.getCellMeasure();
}

// Méthode des trapèzes
Point Trapezoidal::integrate() const {
    size_t nx = grid.getNx();
    size_t ny = (grid.getDimension() >= 2) ? grid.getNy() : 1;
    size_t nz = (grid.getDimension() >= 3) ? grid.getNz() : 1;
    Point sum = func.evaluate(grid.getCellCenter(0, 0, 0));
    sum = sum * 0.0;
    for (size_t k = 0; k < nz; k++) {
        for (size_t j = 0; j < ny; j++) {
            for (size_t i = 0; i < nx; i++) {
                if (grid.getDimension() == 1) {
                    sum = sum + (func.evaluate(grid.getPoint(i)) + func.evaluate(grid.getPoint(i + 1))) * 0.5;
                } else if (grid.getDimension() == 2) {
                    sum = sum + (func.evaluate(grid.getPoint(i, j))
                                 + func.evaluate(grid.getPoint(i + 1, j))
                                 + func.evaluate(grid.getPoint(i, j + 1))
                                 + func.evaluate(grid.getPoint(i + 1, j + 1))) * 0.25;
                } else {
                    sum = sum + (func.evaluate(grid.getPoint(i, j, k))
                                 + func.evaluate(grid.getPoint(i + 1, j, k))
                                 + func.evaluate(grid.getPoint(i, j + 1, k))
                                 + func.evaluate(grid.getPoint(i + 1, j + 1, k))
                                 + func.evaluate(grid.getPoint(i, j, k + 1))
                                 + func.evaluate(grid.getPoint(i + 1, j, k + 1))
                                 + func.evaluate(grid.getPoint(i, j + 1, k + 1))
                                 + func.evaluate(grid.getPoint(i + 1, j + 1, k + 1))) * 0.125;
                }
            }
        }
    }
    return sum * grid.getCellMeasure();
}

// Méthode des trapèzes
Point Simpson::integrate() const {
    size_t nx = grid.getNx();
    size_t ny = (grid.getDimension() >= 2) ? grid.getNy() : 1;
    size_t nz = (grid.getDimension() >= 3) ? grid.getNz() : 1;
    Point sum = func.evaluate(grid.getCellCenter(0, 0, 0));
    sum = sum * 0.0;
    if (nx % 2 != 0 || (grid.getDimension() >= 2 && ny % 2 != 0) || (grid.getDimension() >= 3 && nz % 2 != 0)) {
        throw std::invalid_argument("Le nombre de subdivisions doit etre pair pour Simpson.");
    }
    for (size_t k = 0; k < nz; k++) {
        for (size_t j = 0; j < ny; j++) {
            for (size_t i = 0; i < nx; i++) {
                double wi = (i == 0 || i == nx) ? 1 : (i % 2 == 1 ? 4 : 2);
                double wj = (j == 0 || j == ny) ? 1 : (j % 2 == 1 ? 4 : 2);
                double wk = (k == 0 || k == nz) ? 1 : (k % 2 == 1 ? 4 : 2);
                sum = sum + func.evaluate(grid.getPoint(i, j, k)) * wi * wj * wk;
            }
        }
    }
    double factor = grid.getCellMeasure() / 3.0;
    if (grid.getDimension() >= 2)
        factor /= 3.0;
    if (grid.getDimension() >= 3)
        factor /= 3.0;
    return sum * factor;
}
