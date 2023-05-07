#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "genericobject.h"

class ViewPort : public GenericObject
{
    std::array<Matrix<3, 1>, 4> points;
public:
    ViewPort(const std::array<Matrix<3, 1>, 4>& points);
    virtual void draw(QPainter *painter) override;
};

#endif // VIEWPORT_H
