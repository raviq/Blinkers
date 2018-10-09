#include "myframe.h"
#include "ui_myframe.h"
#include <QDebug>
#include <QColor>

QColor COLOR_CODES [] = { // http://www.rapidtables.com/web/color/RGB_Color.htm
                          QColor(255,0,0),        // red
                          QColor(0,255,0),        // green
                          QColor(0,0,255),        // blue
                          QColor(255,255,255),    // white
                          QColor(75,0,130),       // purple
                          QColor(255,140,0),      // orange
                          QColor(255,192,203),    // pink
                          QColor(128,128,0),      // Olive
                          QColor(0,0,128),        // Navy
                          QColor(250,128,114),    // Salmon
                          QColor(255,255,0),      // Yellow
                          QColor(224,255,255),    // Light cyan
                          QColor(245,222,179),    // wheat
                          QColor(210,105,30),     // chocolate
                          QColor(230,230,250)    // Lavender
                      };

//=======================================================================================================================
MyFrame::MyFrame(QWidget *parent) :  QFrame(parent), ui(new Ui::MyFrame)
{
    /*
    QPainterPath path;
    path.addRoundedRect(QRectF(20, 20, 20, 20), 10, 10);
    QRegion region = QRegion(path.toFillPolygon().toPolygon());
    setMask(region);
*/

/*
    QPalette Pal(palette());
   QPixmap* pixmap = new QPixmap("/new/prefix1/images/smiley1.jpeg");
    Pal.setBrush(QPalette::Background, QBrush(*pixmap));
    //setAutoFillBackground(true);
    setPalette(Pal);
*/
/*
    QPalette Pal(palette());
    pal.setBrush( backgroundRole(), QBrush( QImage("/new/prefix1/images/smiley1.jpeg") ) );
    setPalette(pal);
*/
    setColor(Qt::white);
    setFrameStyle(QFrame::Box);
    setFixedSize(50, 50);
}

//=======================================================================================================================
QColor MyFrame::getFrameColor()
{
    return FrameColor;
}
//=======================================================================================================================
const char* MyFrame::getFrameColorName()
{
    return FrameColorName;
}
//=======================================================================================================================
void MyFrame::setColor(QColor qtcolor)
{
    // Set initial color: white.
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, qtcolor);

    setAutoFillBackground(true);
    setPalette(Pal);
}
//=======================================================================================================================

void MyFrame::randomizeColor(int i)
{
    int n = sizeof(COLOR_CODES) / sizeof(QColor);
    FrameColor = COLOR_CODES[rand() % n]; // random number between 0 and (n-1) as index

    setColor(FrameColor);

    //setWindowOpacity(0.5);

    emit frameColorChanged(FrameColor, i);
}
//=======================================================================================================================


MyFrame::~MyFrame()
{
    delete ui;
}
