//
// Created by Theo on 26.11.2026.
//

#include "Grid.h"


// Constructeur 1D
Grid::Grid(std::initializer_list<double> x, std::size_t Nx)
    : nx(Nx), ny(0), nz(0), dim(1) {
    auto it = x.begin();
    xmin = *it;
    xmax = *(it + 1);
    ymin = ymax = 0.0;
    zmin = zmax = 0.0;
    buildGrid();
}

// Constructeur 2D
Grid::Grid(std::initializer_list<double> x, std::size_t Nx, std::initializer_list<double> y, std::size_t Ny)
    : nx(Nx), ny(Ny), nz(0), dim(2) {
    auto ix = x.begin();
    auto iy = y.begin();
    xmin = *ix;
    xmax = *(ix + 1);
    ymin = *iy;
    ymax = *(iy + 1);
    zmin = zmax = 0.0;
    buildGrid();
}

// Constructeur 3D
Grid::Grid(std::initializer_list<double> x, std::size_t Nx, std::initializer_list<double> y, std::size_t Ny, std::initializer_list<double> z,
     std::size_t Nz)
    : nx(Nx), ny(Ny), nz(Nz), dim(3) {
    auto ix = x.begin();
    auto iy = y.begin();
    auto iz = z.begin();
    xmin = *ix;
    xmax = *(ix + 1);
    ymin = *iy;
    ymax = *(iy + 1);
    zmin = *iz;
    zmax = *(iz + 1);
    buildGrid();
}

// Construction automatique du grillage
void Grid::buildGrid() {
    points.clear();
    double hx = (xmax - xmin) / nx;
    double hy = (dim >= 2) ? (ymax - ymin) / ny : 0.0;
    double hz = (dim >= 3) ? (zmax - zmin) / nz : 0.0;

    for (size_t k = 0; k <= nz; k++) {
        for (size_t j = 0; j <= ny; j++) {
            for (size_t i = 0; i <= nx; i++) {
                double px = xmin + i * hx;
                double py = ymin + j * hy;
                double pz = zmin + k * hz;

                if (dim == 1)
                    points.push_back(Point{px});
                else if (dim == 2)
                    points.push_back(Point{px, py});
                else
                    points.push_back(Point{px, py, pz});
            }
        }
    }
}

// Récupérer un sommet
Point Grid::getPoint(std::size_t i, std::size_t j, std::size_t k ) const {
    size_t index = k * (ny + 1) * (nx + 1) + j * (nx + 1) + i;
    return points.at(index);
}

// Centre d'une cellule
Point Grid::getCellCenter(std::size_t i, std::size_t j, std::size_t k) const {
    double x = xmin + (i + 0.5) * (xmax - xmin) / nx;
    if (dim == 1)
        return Point{x};
    double y = ymin + (j + 0.5) * (ymax - ymin) / ny;
    if (dim == 2)
        return Point{x, y};
    double z = zmin + (k + 0.5) * (zmax - zmin) / nz;
    return Point{x, y, z};
}

std::size_t Grid::getNx() const { return nx; }
std::size_t Grid::getNy() const { return ny; }
std::size_t Grid::getNz() const { return nz; }
std::size_t Grid::getDimension() const { return dim; }

double Grid::getCellMeasure() const {
    double hx = (xmax - xmin) / nx;
    if (dim == 1)
        return hx;
    double hy = (ymax - ymin) / ny;
    if (dim == 2)
        return hx * hy;
    double hz = (zmax - zmin) / nz;
    return hx * hy * hz;
}

