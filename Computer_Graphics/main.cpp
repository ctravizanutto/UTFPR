#include "mainwindow.h"
#include <QApplication>

#include <stdlib.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.resize(1280, 720);
    w.setWindowTitle("CC54E");
    w.show();

    return a.exec();
}
