#ifndef MYFRAME_H
#define MYFRAME_H

#include <QFrame>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <vector>

#include "genericobject.h"
#include "rectangle.h"
#include "viewport.h"

class MyFrame : public QFrame
{
    std::vector<GenericObject*> displayFile;

public:
    explicit MyFrame(QWidget *parent = nullptr);
    ~MyFrame();
    void paintEvent(QPaintEvent *event) override;

private:
    Q_OBJECT

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

#endif // MYFRAME_H
