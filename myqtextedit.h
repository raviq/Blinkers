#ifndef MYQTEXTEDIT_H
#define MYQTEXTEDIT_H

#include <QTextEdit>
#include <QDebug>
#include <QTime>
#include <QPalette>

class MyQTextEdit : public QTextEdit
{

public:

    explicit MyQTextEdit(QWidget *parent = 0);
    void add(QString cont);

private:
    QString content;

public slots:
    void notify(const char* col);


};

#endif // MYQTEXTEDIT_H
