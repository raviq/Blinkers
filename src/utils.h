#ifndef UTILS_H
#define UTILS_H

#include <QThread>

float random(float from, float to)
{
    return from + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(to-from)));
}

class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs) { QThread::usleep(usecs); }
    static void msleep(unsigned long msecs) { QThread::msleep(msecs); }
    static void sleep(unsigned long secs)   { QThread::sleep(secs);   }
};


#endif // UTILS_H
