#include "myframe.h"

MyFrame::MyFrame(QWidget *parent): QFrame{parent}
{
    std::array<Matrix<3, 1>, 4> viewport_coords {
        Matrix<3, 1>(10.0, 10.0, 1.0),
        Matrix<3, 1>(960.0, 10.0, 1.0),
        Matrix<3, 1>(10.0, 540.0, 1.0),
        Matrix<3, 1>(960.0, 540.0, 1.0)
    };
    auto viewport = new ViewPort(viewport_coords);
    displayFile.push_back(viewport);

    std::array<Matrix<3, 1>, 4> rect_coords {{
        Matrix<3, 1>(100.0, 100.0, 1.0),
        Matrix<3, 1>(200.0, 100.0, 1.0),
        Matrix<3, 1>(100.0, 200.0, 1.0),
        Matrix<3, 1>(200.0, 200.0, 1.0)
    }};
    auto rect = new Rectangle(nullptr, rect_coords);
    displayFile.push_back(rect);
}

MyFrame::~MyFrame()
{
    for (GenericObject* object: displayFile)
        delete object;
}


void MyFrame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    QPainter painter(this);

    for (GenericObject* object: displayFile)
        object->draw(&painter);

}

void MyFrame::rect_rot_r()
{
    //displayFile[0]->rotate(PI / 3);
    update();
}

void MyFrame::rect_rot_l()
{
    //displayFile[0]->rotate(-PI / 3);
    update();
}

void MyFrame::rect_inc()
{
    //displayFile[0]->rescale(2, 2);
    update();
}

void MyFrame::rect_dec()
{
    //displayFile[0]->rescale(0.5, 0.5);
    update();
}

void MyFrame::rect_up()
{
    //displayFile[0]->translation(0.0, -1.0);
    update();
}

void MyFrame::rect_down()
{
    //displayFile[0]->translation(0.0, 1.0);
    update();
}

void MyFrame::rect_left()
{
    //displayFile[0]->translation(-1.0, 0.0);
    update();
}

void MyFrame::rect_right()
{
    //displayFile[0]->translation(1.0, 0.0);
    update();
}

