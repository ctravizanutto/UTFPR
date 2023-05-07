/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "my_frame.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    my_frame *frame;
    QLabel *label;
    QPushButton *left_rotate_rect;
    QPushButton *right_rotate_rect;
    QPushButton *inc_size_rect;
    QPushButton *dec_size_rect;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 763);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(1280, 720));
        centralwidget->setCursor(QCursor(Qt::ArrowCursor));
        frame = new my_frame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(100, 10, 1171, 721));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 40, 61, 16));
        left_rotate_rect = new QPushButton(centralwidget);
        left_rotate_rect->setObjectName("left_rotate_rect");
        left_rotate_rect->setGeometry(QRect(20, 60, 21, 24));
        right_rotate_rect = new QPushButton(centralwidget);
        right_rotate_rect->setObjectName("right_rotate_rect");
        right_rotate_rect->setGeometry(QRect(50, 60, 21, 24));
        inc_size_rect = new QPushButton(centralwidget);
        inc_size_rect->setObjectName("inc_size_rect");
        inc_size_rect->setGeometry(QRect(20, 90, 21, 24));
        dec_size_rect = new QPushButton(centralwidget);
        dec_size_rect->setObjectName("dec_size_rect");
        dec_size_rect->setGeometry(QRect(50, 90, 21, 24));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(35, 120, 21, 24));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(35, 160, 21, 24));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(60, 140, 21, 24));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(10, 140, 21, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1280, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(dec_size_rect, &QPushButton::clicked, frame, qOverload<>(&my_frame::rect_dec));
        QObject::connect(inc_size_rect, &QPushButton::clicked, frame, qOverload<>(&my_frame::rect_inc));
        QObject::connect(pushButton, &QPushButton::clicked, frame, qOverload<>(&my_frame::rect_up));
        QObject::connect(pushButton_3, &QPushButton::clicked, frame, qOverload<>(&my_frame::rect_right));
        QObject::connect(pushButton_2, &QPushButton::clicked, frame, qOverload<>(&my_frame::rect_down));
        QObject::connect(pushButton_4, &QPushButton::clicked, frame, qOverload<>(&my_frame::rect_left));
        QObject::connect(right_rotate_rect, &QPushButton::clicked, frame, qOverload<>(&my_frame::rect_rot_r));
        QObject::connect(left_rotate_rect, &QPushButton::clicked, frame, qOverload<>(&my_frame::rect_rot_l));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Quadrado", nullptr));
        left_rotate_rect->setText(QCoreApplication::translate("MainWindow", "\342\244\271", nullptr));
        right_rotate_rect->setText(QCoreApplication::translate("MainWindow", "\342\244\270", nullptr));
        inc_size_rect->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        dec_size_rect->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\342\206\221", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\342\206\223", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\342\206\222", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\342\206\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
