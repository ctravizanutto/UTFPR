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
#include "window.h"

class MyFrame : public QFrame
{
    Q_OBJECT
    std::vector<std::unique_ptr<GenericObject>> displayFile;

public:
    explicit MyFrame(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

public slots:

signals:

};

#endif // MYFRAME_H
