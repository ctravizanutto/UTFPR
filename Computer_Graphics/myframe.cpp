#include "myframe.h"

MyFrame::MyFrame(QWidget *parent): QFrame{parent}
{
    std::array<Matrix<3, 1>, 4> viewport_coords {
        Matrix<3, 1>(10.0, 10.0, 1.0),
        Matrix<3, 1>(960.0, 10.0, 1.0),
        Matrix<3, 1>(10.0, 540.0, 1.0),
        Matrix<3, 1>(960.0, 540.0, 1.0)
    };
    displayFile.push_back(std::make_unique<ViewPort>(viewport_coords));
    displayFile.push_back(std::make_unique<Window>(viewport_coords));

    std::array<Matrix<3, 1>, 4> rect_coords {{
        Matrix<3, 1>(100.0, 100.0, 1.0),
        Matrix<3, 1>(200.0, 100.0, 1.0),
        Matrix<3, 1>(100.0, 200.0, 1.0),
        Matrix<3, 1>(200.0, 200.0, 1.0)
    }};
    displayFile.push_back(std::make_unique<Rectangle>(nullptr, rect_coords));
}

void MyFrame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    QPainter painter(this);

    for (auto const& object: displayFile)
        object->draw(&painter);
}
