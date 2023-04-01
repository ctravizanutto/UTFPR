#include "triangle.h"

Triangle::Triangle(const std::string& name, QPointF top, QPointF left, QPointF right)
    : GenericObject(name), top(top), left(left), right(right)
{

}

void Triangle::draw(QPainter *painter) {
    painter->setPen(QPen(Qt::blue, 2));

    painter->drawLine(top, left);
    painter->drawLine(top, right);
    painter->drawLine(left, right);
}

std::string Triangle::get_type() {
    return "Triangle";
}
