#include "window.h"

Window::Window(const std::array<Matrix<3, 1>, 4>& points) : points(points)
{
    this->name = std::make_unique<std::string>("window");
}
