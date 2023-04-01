#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "genericobject.h"

class Triangle : public GenericObject
{
    QPointF top;
    QPointF left;
    QPointF right;

public:
    Triangle(const std::string& name, QPointF top, QPointF left, QPointF right);
    ~Triangle() {}
    virtual void draw(QPainter *painter) override;
    virtual std::string get_type() override;
};

#endif // TRIANGLE_H
