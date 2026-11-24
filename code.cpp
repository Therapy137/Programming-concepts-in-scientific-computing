#include <math.h>
#include <iostream>
#include <functional>
#include <iomanip>
#include <vector>
#include <cmath>
#include <initializer_list>
#include <stdexcept>

using namespace std;

class Point{
    private:
        vector<double> p;
    public:
        Point(initializer_list<double> values) : p(values) {}

        double operator[](size_t i) const {
            return p.at(i);}

        Point operator+(const Point& other) const {
            if (p.size() != other.p.size())
                throw invalid_argument("Dimensions incompatibles");
            Point result = *this;
            for (size_t i = 0; i < p.size(); i++)
                result.p[i] += other.p[i];
            return result;}

        Point operator-(const Point& other) const {
            if (p.size() != other.p.size())
                throw invalid_argument("Dimensions incompatibles");
            Point result = *this;
            for (size_t i = 0; i < p.size(); i++)
                result.p[i] -= other.p[i];
            return result;}

        Point operator*(double scalar) const {
        Point result = *this;
        for (size_t i = 0; i < p.size(); i++)
            result.p[i] *= scalar;
        return result;}

        size_t dimension() const {
            return p.size();}
};


class Grid {
    private:
        size_t nx, ny, nz;
        double xmin, xmax, ymin, ymax, zmin, zmax;
        size_t dim;
        vector<Point> points;

    public:
        // Constructeur 1D
        Grid(initializer_list<double> x, size_t Nx)
            : nx(Nx), ny(0), nz(0), dim(1) {
            auto it = x.begin();
            xmin = *it;
            xmax = *(it + 1);
            ymin = ymax = 0.0;
            zmin = zmax = 0.0;
            buildGrid(); }

        // Constructeur 2D
        Grid(initializer_list<double> x, size_t Nx, initializer_list<double> y, size_t Ny)
            : nx(Nx), ny(Ny), nz(0), dim(2) {
            auto ix = x.begin();
            auto iy = y.begin();
            xmin = *ix;
            xmax = *(ix + 1);
            ymin = *iy;
            ymax = *(iy + 1);
            zmin = zmax = 0.0;
            buildGrid(); }

        // Constructeur 3D
        Grid(initializer_list<double> x, size_t Nx,initializer_list<double> y, size_t Ny,initializer_list<double> z, size_t Nz)
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
            buildGrid(); }

    // Construction automatique du grillage
        void buildGrid() {
            points.clear();
            double hx = (xmax - xmin) / nx;
            double hy = (dim >= 2) ? (ymax - ymin) / ny : 0.0;
            double hz = (dim >= 3) ? (zmax - zmin) / nz : 0.0;

            for (size_t k = 0; k <= nz; k++) {
                for (size_t j = 0; j <= ny; j++) {
                    for (size_t i = 0; i <= nx; i++){
                        double px = xmin + i * hx;
                        double py = ymin + j * hy;
                        double pz = zmin + k * hz;

                        if (dim == 1)
                            points.push_back(Point{px});
                        else if (dim == 2)
                            points.push_back(Point{px, py});
                        else
                            points.push_back(Point{px, py, pz}); }}}}

        // Récupérer un sommet
        Point getPoint(size_t i, size_t j = 0, size_t k = 0) const {
            size_t index = k * (ny + 1) * (nx + 1) + j * (nx + 1) + i;
            return points.at(index); }

        // Centre d'une cellule
        Point getCellCenter(size_t i, size_t j = 0, size_t k = 0) const {
            double x = xmin + (i + 0.5) * (xmax - xmin) / nx;
            if (dim == 1)
                return Point{x};
            double y = ymin + (j + 0.5) * (ymax - ymin) / ny;
            if (dim == 2)
                return Point{x, y};
            double z = zmin + (k + 0.5) * (zmax - zmin) / nz;
            return Point{x, y, z}; }

        size_t getNx() const {return nx;}
        size_t getNy() const {return ny;}
        size_t getNz() const {return nz;}
        size_t getDimension() const {return dim;}

        double getCellMeasure() const {
            double hx = (xmax - xmin) / nx;
            if (dim == 1)
                return hx;
            double hy = (ymax - ymin) / ny;
            if (dim == 2)
                return hx * hy;
            double hz = (zmax - zmin) / nz;
            return hx * hy * hz;}
};

class Functions {
    private:
        function<Point(const Point&)> f;
    public:
        Functions(function<Point(const Point&)> func)
            : f(func) {}
        Point evaluate(const Point& p) const { return f(p);}
};

class Integration {
    private:
        Grid grid;
        Functions func;
    public:
        // Constructeur
        Integration(const Grid& g, const Functions& f)
            : grid(g), func(f) {}
        // Méthode du point milieu
        Point midpoint() const {
            size_t nx = grid.getNx();
            size_t ny = (grid.getDimension() >= 2) ? grid.getNy() : 1;
            size_t nz = (grid.getDimension() >= 3) ? grid.getNz() : 1;
            Point sum = func.evaluate(grid.getCellCenter(0, 0, 0));
            sum = sum * 0.0;
            for (size_t k = 0; k < nz; k++) {
                for (size_t j = 0; j < ny; j++) {
                    for (size_t i = 0; i < nx; i++) {
                        Point center = grid.getCellCenter(i, j, k);
                        sum = sum + func.evaluate(center);}}}
            return sum * grid.getCellMeasure();}

        // Méthode des trapèzes
        Point trapezoidal() const {
        size_t nx = grid.getNx();
        size_t ny = (grid.getDimension() >= 2) ? grid.getNy() : 1;
        size_t nz = (grid.getDimension() >= 3) ? grid.getNz() : 1;
        Point sum = func.evaluate(grid.getCellCenter(0, 0, 0));
        sum = sum * 0.0;
        for (size_t k = 0; k < nz; k++) {
            for (size_t j = 0; j < ny; j++) {
                for (size_t i = 0; i < nx; i++) {
                    if (grid.getDimension() == 1) {
                        sum = sum +(func.evaluate(grid.getPoint(i)) + func.evaluate(grid.getPoint(i + 1))) * 0.5;}

                    else if (grid.getDimension() == 2) {
                        sum = sum + (func.evaluate(grid.getPoint(i, j))
                            + func.evaluate(grid.getPoint(i + 1, j))
                            + func.evaluate(grid.getPoint(i, j + 1))
                            + func.evaluate(grid.getPoint(i + 1, j + 1))) * 0.25;
                    }else {
                        sum = sum + (func.evaluate(grid.getPoint(i, j, k))
                            + func.evaluate(grid.getPoint(i + 1, j, k))
                            + func.evaluate(grid.getPoint(i, j + 1, k))
                            + func.evaluate(grid.getPoint(i + 1, j + 1, k))
                            + func.evaluate(grid.getPoint(i, j, k + 1))
                            + func.evaluate(grid.getPoint(i + 1, j, k + 1))
                            + func.evaluate(grid.getPoint(i, j + 1, k + 1))
                            + func.evaluate(grid.getPoint(i + 1, j + 1, k + 1))) * 0.125;}}}}
        return sum * grid.getCellMeasure();}   

        // Méthode des trapèzes
        Point simpson() const {
        size_t nx = grid.getNx();
        size_t ny = (grid.getDimension() >= 2) ? grid.getNy() : 1;
        size_t nz = (grid.getDimension() >= 3) ? grid.getNz() : 1;
        Point sum = func.evaluate(grid.getCellCenter(0, 0, 0));
        sum = sum * 0.0;
        if (nx % 2 != 0 || (grid.getDimension() >= 2 && ny % 2 != 0) || (grid.getDimension() >= 3 && nz % 2 != 0)) {throw invalid_argument("Le nombre de subdivisions doit etre pair pour Simpson.");}
        for (size_t k = 0; k < nz; k++) {
            for (size_t j = 0; j < ny; j++) {
                for (size_t i = 0; i < nx; i++) {
                    double wi = (i == 0 || i == nx) ? 1 : (i % 2 == 1 ? 4 : 2);
                    double wj = (j == 0 || j == ny) ? 1 : (j % 2 == 1 ? 4 : 2);
                    double wk = (k == 0 || k == nz) ? 1 : (k % 2 == 1 ? 4 : 2);
                    sum = sum + func.evaluate(grid.getPoint(i, j, k))*wi*wj*wk ;}}}
        double factor = grid.getCellMeasure() / 3.0;
        if (grid.getDimension() >= 2)
            factor /= 3.0;
        if (grid.getDimension() >= 3)
            factor /= 3.0;
        return sum * factor;}
};

int main() {

    cout << fixed << setprecision(8);

    Grid grid2D({0.0, M_PI}, 100, {0, 1}, 100);

    Functions f2([](const Point& p) {
    double x = p[0];
    double y = p[1];

    return Point{
        x * sin(x * y),
        x * cos(x * y),
        x * y};});

    Integration I2(grid2D, f2);

    Point resultM = I2.midpoint();
    Point resultT = I2.trapezoidal();
    Point resultS = I2.simpson();

    cout << "\nTest R^2 -> R^3 :" << endl;

    cout << "Milieu : "
        << resultM[0] << "  "
        << resultM[1] << "  "
        << resultM[2] << endl;

    cout << "Trapezes : "
        << resultT[0] << "  "
        << resultT[1] << "  "
        << resultT[2] << endl;

    cout << "Simpson : "
        << resultS[0] << "  "
        << resultS[1] << "  "
        << resultS[2] << endl;

    return 0;
}