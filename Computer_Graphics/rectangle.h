#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "genericobject.h"

class Rectangle : public GenericObject
{
    std::array<Matrix<3, 1>, 4> world_coords;
    std::array<Matrix<3, 1>, 4> window_coords;
    double dx, dy;
    double sx;
    bool clipped;

public:
    Rectangle(const char* name, const std::array<Matrix<3, 1>, 4>& points);

    virtual void draw(QPainter *painter) override;
    virtual void transform(Matrix<3, 3>&, CoordType) override;
    virtual void clip() override;
};

#endif // RECTANGLE_H
