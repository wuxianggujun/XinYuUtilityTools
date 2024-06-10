#include "mainwindow.h"

#include <string>
#include <QApplication>
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int result = a.exec();
    return result;
}
