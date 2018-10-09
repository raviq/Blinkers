#ifndef MYFRAME_H
#define MYFRAME_H

#include <QFrame>
#include <QColor>
#include <QPalette>
#include <QTextEdit>

namespace Ui
{
    class MyFrame;
}

class MyFrame : public QFrame
{
    Q_OBJECT

public:
    explicit MyFrame(QWidget *parent = 0);
    ~MyFrame();
    void setColor(QColor);
    QColor getFrameColor();
    const char* getFrameColorName();
    void randomizeColor(int i);

private:
    Ui::MyFrame *ui;
    QColor FrameColor;
    const char* FrameColorName;
    QPixmap pixmap;



//public slots:
signals:
    void frameColorChanged(QColor FrameColor, int i);

};


#endif // MYFRAME_H
