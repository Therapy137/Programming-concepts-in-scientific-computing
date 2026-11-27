//
// Created by Theo on 26.11.2026.
//

#ifndef MYPROJECT_GRID_H
#define MYPROJECT_GRID_H
#include <vector>
#include "Point.h"

class Grid {
protected:
    std::size_t nx, ny, nz;
    double xmin, xmax, ymin, ymax, zmin, zmax;
    std::size_t dim;
    std::vector<Point> points;
public:
    Grid(std::initializer_list<double> x, std::size_t Nx);
    Grid(std::initializer_list<double> x, std::size_t Nx, std::initializer_list<double> y, std::size_t Ny);
    Grid(std::initializer_list<double> x, std::size_t Nx, std::initializer_list<double> y, std::size_t Ny, std::initializer_list<double> z,
     std::size_t Nz);
    virtual double jacobian(const Point &p) const;
    virtual ~Grid() = default;
    virtual void buildGrid();
    Point getPoint(std::size_t i, std::size_t j=0, std::size_t k=0) const;
    virtual Point getCellCenter(std::size_t i, std::size_t j =0, std::size_t k=0) const;
    std::size_t getNx() const;
    std::size_t getNy() const;
    std::size_t getNz() const;
    std::size_t getDimension() const;
    double getCellMeasure() const ;

};
class Square : public Grid {
public:
    using Grid::Grid;
    void buildGrid() override;
    double jacobian(const Point &p) const override;
};
class Circle : public Grid {
private:
    double radius;
    std::vector<double> center;

public:

    Circle(std::initializer_list<double> coords, double r, std::size_t Nx, std::size_t Ny);
    Circle(std::initializer_list<double> coords, double r, std::size_t Nx, std::size_t Ny, std::size_t Nz);
    void buildGrid() override;
    Point getCellCenter(std::size_t i, std::size_t j, std::size_t k) const override;
    double jacobian(const Point &p) const override;

};

#endif //MYPROJECT_GRID_H
