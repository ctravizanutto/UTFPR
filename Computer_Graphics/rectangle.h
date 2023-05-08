#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "genericobject.h"

class Rectangle : public GenericObject
{
    std::array<Matrix<3, 1>, 4> world_coords;
    std::array<Matrix<3, 1>, 4> window_coords;
    double dx, dy;
    double sx;
    bool clipped = true;

public:
    Rectangle(const char* name, const std::array<Matrix<3, 1>, 4>& points);

    void draw(QPainter*) override;
    void transform(Matrix<3, 3>&, CoordType) override;
    void clip() override;

    void rescale(double sx, double sy);
    void rotate(double o);
    void translation(double dx, double dy);
};

#endif // RECTANGLE_H
