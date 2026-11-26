//
// Created by Theo on 26.11.2026.
//

#ifndef MYPROJECT_INTEGRATION_H
#define MYPROJECT_INTEGRATION_H

#include "Grid.h"
#include "Functions.h"

class Integration {
protected:
    Grid grid;
    Functions func;
public:
    Integration(const Grid &g, const Functions &f);
    virtual ~Integration() = default;
    virtual Point integrate() const =0;
};
class Midpoint : public Integration {
public:
    using Integration::Integration;
    Point integrate() const override;
};
class Trapezoidal : public Integration {
public:
    using Integration::Integration;
    Point integrate() const override;
};
class Simpson : public Integration {
public:
    using Integration::Integration;
    Point integrate() const override;
};

#endif //MYPROJECT_INTEGRATION_H
