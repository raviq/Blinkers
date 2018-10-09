
#include <QApplication>

#include "mainwindow.h"

#include "gct.h"

int main(int argc, char *argv[])
{
    // testing GCT
    //GCT gct = GCT();
    //gct.test();
    //return 0;


    int numberOfCells = 4;
    QApplication a(argc, argv);
    //QApplication::setWindowIcon(QIcon(":/images/borrom.png"));

    MainWindow w(0, numberOfCells);
    w.show();



    return a.exec();
}
