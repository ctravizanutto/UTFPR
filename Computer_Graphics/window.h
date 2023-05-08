#ifndef WINDOW_H
#define WINDOW_H

#include "genericobject.h"

class Window : public GenericObject
{
    std::array<Matrix<3, 1>, 4> points;
    Matrix<3, 3> t;
    std::array<double, 2> view_up;

public:
    Window(const std::array<Matrix<3, 1>, 4>& points);

    void clip_and_transform();
};

#endif // WINDOW_H
