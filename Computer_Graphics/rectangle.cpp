#include "rectangle.h"

#include <unistd.h>

Rectangle::Rectangle(const char* name, const std::array<Matrix<3, 1>, 4>& world_coords) : world_coords(world_coords)
{
    dx = world_coords[0](0, 0), dy = world_coords[0](0, 1);
    if (name)
        this->name = std::make_unique<std::string>(name);
}

void Rectangle::draw(QPainter *painter) {
    /*this->clip();
    if (clipped)
        return;

    // TODO*/

    painter->setPen(QPen(Qt::black, 1));

    painter->drawLine(world_coords[0].get_coords(), world_coords[1].get_coords());
    painter->drawLine(world_coords[0].get_coords(), world_coords[2].get_coords());
    painter->drawLine(world_coords[1].get_coords(), world_coords[3].get_coords());
    painter->drawLine(world_coords[2].get_coords(), world_coords[3].get_coords());
    (*this).translation(110, 0);

    (*this).rescale(1.5, 1.5);
    painter->drawLine(world_coords[0].get_coords(), world_coords[1].get_coords());
    painter->drawLine(world_coords[0].get_coords(), world_coords[2].get_coords());
    painter->drawLine(world_coords[1].get_coords(), world_coords[3].get_coords());
    painter->drawLine(world_coords[2].get_coords(), world_coords[3].get_coords());
    (*this).translation(300, 0);

    (*this).rotate(PI / 4);
    painter->drawLine(world_coords[0].get_coords(), world_coords[1].get_coords());
    painter->drawLine(world_coords[0].get_coords(), world_coords[2].get_coords());
    painter->drawLine(world_coords[1].get_coords(), world_coords[3].get_coords());
    painter->drawLine(world_coords[2].get_coords(), world_coords[3].get_coords());
}

void Rectangle::transform(Matrix<3, 3> &t, CoordType coord_type)
{
    switch (coord_type) {
        case CoordType::world:
            for (auto& point: world_coords) {
                point = t * point;
            }
            break;
        case CoordType::window:
            break;
        default:
            break;
    }
}

void Rectangle::clip()
{
    // TODO
}

void Rectangle::rotate(double o)
{
    Matrix<3, 3> mat = {cos(o), -sin(o), dx - cos(o) * dx + sin(o) * dy,
                        sin(o), cos(o), dy - sin(o) * dx - cos(o) * dy,
                        0.0, 0.0, 1.0};

    for (auto& point: world_coords) {
        point = mat * point;
    }
}

void Rectangle::translation(double dx, double dy)
{
    Matrix<3, 3> mat = {1.0, 0.0, dx,
                        0.0, 1.0, dy,
                        0.0, 0.0, 1.0};

    for (auto& point: world_coords) {
        point = mat * point;
    }
    this->dx = world_coords[0](0, 0), this->dy = world_coords[0](0, 1);
}

void Rectangle::rescale(double sx, double sy)
{
    Matrix<3, 3> mat = {sx,  0.0, dx * (1 - sx),
                        0.0, sy,  dy * (1 - sy),
                        0.0, 0.0, 1.0};

    for (auto& point: world_coords) {
        point = mat * point;
    }
}


