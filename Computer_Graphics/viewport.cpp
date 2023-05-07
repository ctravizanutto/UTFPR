#include "viewport.h"

ViewPort::ViewPort(const std::array<Matrix<3, 1>, 4>& points) : points(points)
{
    this->name = new std::string("viewport");
}

void ViewPort::draw(QPainter *painter) {
    painter->setPen(QPen(Qt::black, 2));

    painter->drawLine(points[0].get_coords(), points[1].get_coords());
    painter->drawLine(points[0].get_coords(), points[2].get_coords());
    painter->drawLine(points[1].get_coords(), points[3].get_coords());
    painter->drawLine(points[2].get_coords(), points[3].get_coords());
}
