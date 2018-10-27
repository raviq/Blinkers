// Blinkers' main entry
// Rafik Hadfi <rafik.hadfi@gmail.com>

#include <QApplication>
#include "mainwindow.h"
#include "gct.h"

int main(int argc, char *argv[])
{
    /// Testing GCT
    // GCT gct = GCT();
    // gct.test();
    // return 0;

    int numberOfCells = 4;
    QApplication a(argc, argv);
    MainWindow w(0, numberOfCells);
    w.show();

    return a.exec();
}
