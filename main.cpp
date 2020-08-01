#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QDesktopWidget dw;
    w.resize(dw.width()*0.5,dw.height()*0.5);//設定初始視窗大小
    w.show();
    return a.exec();
}
