#include "myqtextedit.h"

MyQTextEdit::MyQTextEdit(QWidget *parent) : QTextEdit(parent)
{
    // setting palette using FrameEditorPalette (for the background).
    QPalette FrameEditorPalette = this->palette();
    FrameEditorPalette.setColor(QPalette::Base, QColor(228, 230, 236));
    this->setPalette(FrameEditorPalette);

    // content
    content = QTime::currentTime().toString() + "   Init!\n";
    this->setPlainText(content);
}


void MyQTextEdit::add(QString cont)
{
    this->setPlainText(content+"\n"+cont);
}


void MyQTextEdit::notify(const char* col)
{
    qDebug() << col;

    this->add(QTime::currentTime().toString() + " color : " + col);
}
