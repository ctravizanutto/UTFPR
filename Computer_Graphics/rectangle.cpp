#include "rectangle.h"

#include <iostream>

Rectangle::Rectangle(const std::string& name, const std::array<Matrix<3, 1>, 4>& points)
    : GenericObject(name), coords(points)
{
    dx = coords[0](0, 0), dy = coords[0](0, 1);
}

void Rectangle::draw(QPainter *painter) {
    painter->setPen(QPen(Qt::red, 2));

    painter->drawLine(coords[0].get_coords(), coords[1].get_coords());
    painter->drawLine(coords[0].get_coords(), coords[2].get_coords());
    painter->drawLine(coords[1].get_coords(), coords[3].get_coords());
    painter->drawLine(coords[2].get_coords(), coords[3].get_coords());
}

std::string Rectangle::get_type() {
    return "Rectangle";
}

void Rectangle::rotate(double o)
{
    Matrix<3, 3> mat = {cos(o), -sin(o), dx - cos(o) * dx + sin(o) * dy,
                        sin(o), cos(o), dy - sin(o) * dx - cos(o) * dy,
                        0.0, 0.0, 1.0};

    for (auto& point: coords) {
        point = mat * point;
    }
}

void Rectangle::translation(double dx, double dy)
{
    Matrix<3, 3> mat = {1.0, 0.0, dx,
                        0.0, 1.0, dy,
                        0.0, 0.0, 1.0};

    for (auto& point: coords) {
        point = mat * point;
    }
    this->dx = coords[0](0, 0), this->dy = coords[0](0, 1);
}

void Rectangle::rescale(double sx, double sy)
{
    Matrix<3, 3> mat = {sx,  0.0, dx * (1 - sx),
                        0.0, sy,  dy * (1 - sy),
                        0.0, 0.0, 1.0};

    for (auto& point: coords) {
        point = mat * point;
    }
}


