#include "worker.h"
#include "utils.h"

Worker::Worker(MyFrame* myfrm, CLogBook *myFrmEdit, int idx)
{
    index = idx;
    this->myframe = myfrm;
    this->myFrameEditor = myFrmEdit;
}

Worker::~Worker()
{
}

// Start processing data.
void Worker::process()
{
    // TODO should be in different thread, with n-1 others monitoring the other cells or simply updated from one source.

    // min and max waiting time in msec
    float min_wmsec = 0;
    float max_wmsec = 1000;

    for (float dt = 0.0; ; dt = random(min_wmsec, max_wmsec))
    {
         //   dt = 2000; // forcing the periods to be synchronous

       // Ask myframe to set its color to random myframe will set its color to random, emit frameColorChanged,
       // and notify thread with the new color, running notif()
        myframe->randomizeColor(index);
        //qDebug() << this->thread()->currentThreadId() << "   " << QTime::currentTime().toString() << "    dt = " << dt;
        // then, wait for dt, before notifying asking frame again to randomize its colors
        Sleeper::msleep(dt);
    }

    emit finished();
}
