#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "genericobject.h"

class Rectangle : public GenericObject
{
    std::array<Matrix<3, 1>, 4> coords;

public:
    Rectangle(const std::string& name, const std::array<Matrix<3, 1>, 4>& points);
    ~Rectangle() {}

    virtual void draw(QPainter *painter) override;
    virtual std::string get_type() override;
    virtual void rotate(double o) override;
    virtual void translation(double dx, double dy) override;
    virtual void rescale(double sx, double sy) override;

};

#endif // RECTANGLE_H
