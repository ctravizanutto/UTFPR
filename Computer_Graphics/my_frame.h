#ifndef MY_FRAME_H
#define MY_FRAME_H

#include <QFrame>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <vector>

#include <genericobject.h>
#include <rectangle.h>
#include <triangle.h>
#include <array>
#include <matrix.h>


class my_frame : public QFrame
{
    Q_OBJECT

public:
    explicit my_frame(QWidget *parent = nullptr);
    ~my_frame();
    void paintEvent(QPaintEvent *event) override;

    std::vector<GenericObject*> displayFile;

public slots:
    void rect_rot_r();
    void rect_rot_l();
    void rect_inc();
    void rect_dec();
    void rect_up();
    void rect_down();
    void rect_left();
    void rect_right();

signals:

};

#endif // MY_FRAME_H
