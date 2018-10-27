#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QDEBUG>
#include <QTime>
#include "myframe.h"
#include "clogbook.h"

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker(MyFrame* myfrm, CLogBook *myFrmEdit, int idx);
    ~Worker();

public slots:
    void process();

signals:
    void finished();  // when it is done it emits the signal finished() which will then be used to trigger the shutdown of the QThread instance it is contained in.
    void error(QString err);

private:
    int index;
    MyFrame *myframe;
    CLogBook *myFrameEditor;
};





#endif // WORKER_H
