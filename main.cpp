#include "mainscreen.h"
#include <QApplication>
#include"dataconfig.h"
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScreen w;
    w.show();

    return a.exec();
}
