//
// Created by Theo on 26.11.2026.
//

#ifndef MYPROJECT_GRID_H
#define MYPROJECT_GRID_H
#include <vector>
#include "Point.h"

class Grid {
private:
    std::size_t nx, ny, nz;
    double xmin, xmax, ymin, ymax, zmin, zmax;
    std::size_t dim;
    std::vector<Point> points;
public:
    Grid(std::initializer_list<double> x, std::size_t Nx);
    Grid(std::initializer_list<double> x, std::size_t Nx, std::initializer_list<double> y, std::size_t Ny);
    Grid(std::initializer_list<double> x, std::size_t Nx, std::initializer_list<double> y, std::size_t Ny, std::initializer_list<double> z,
     std::size_t Nz);
    void buildGrid();
    Point getPoint(std::size_t i, std::size_t j=0, std::size_t k=0) const;
    Point getCellCenter(std::size_t i, std::size_t j =0, std::size_t k=0) const;
    std::size_t getNx() const;
    std::size_t getNy() const;
    std::size_t getNz() const;
    std::size_t getDimension() const;
    double getCellMeasure() const ;

};


#endif //MYPROJECT_GRID_H
