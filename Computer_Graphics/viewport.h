#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "genericobject.h"

class ViewPort : public GenericObject
{
    std::array<Matrix<3, 1>, 4> points;

public:
    ViewPort(const std::array<Matrix<3, 1>, 4>& points);

    void draw(QPainter*) override;
};

#endif // VIEWPORT_H
