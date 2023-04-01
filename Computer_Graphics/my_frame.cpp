#include "my_frame.h"
#include <string>

#include <iostream>

my_frame::my_frame(QWidget *parent)
    : QFrame{parent}
{  
    std::array<Matrix<3, 1>, 4> rect_coords {{
        Matrix<3, 1>(100.0, 100.0, 1.0),
        Matrix<3, 1>(200.0, 100.0, 1.0),
        Matrix<3, 1>(100.0, 200.0, 1.0),
        Matrix<3, 1>(200.0, 200.0, 1.0)
    }};
    Rectangle* rect = new Rectangle("rect", rect_coords);
    displayFile.push_back(rect);

    Triangle* tri = new Triangle("tri", QPointF(100, 100), QPointF(50, 200), QPointF(150, 200));
    displayFile.push_back(tri);
}

my_frame::~my_frame()
{
    for (GenericObject* object: displayFile)
        delete object;
}


void my_frame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    QPainter painter(this);

    for (GenericObject* object: displayFile)
        object->draw(&painter);

}

void my_frame::rect_rot_r()
{
    displayFile[0]->rotate(1);
    update();
}

void my_frame::rect_rot_l()
{
    displayFile[0]->rotate(-1);
    update();
}

void my_frame::rect_inc()
{
    displayFile[0]->rescale(2, 2);
    update();
}

void my_frame::rect_dec()
{
    displayFile[0]->rescale(0.9, 0.9);
    update();
}

void my_frame::rect_up()
{
    displayFile[0]->translation(0.0, -1);
    update();
}

void my_frame::rect_down()
{
    displayFile[0]->translation(0.0, 1);
    update();
}

void my_frame::rect_left()
{
    displayFile[0]->translation(-1, 0.0);
    update();
}

void my_frame::rect_right()
{
    displayFile[0]->translation(1, 0.0);
    update();
}
