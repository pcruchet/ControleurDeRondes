#ifndef THREADSYNCHRONISATION_H
#define THREADSYNCHRONISATION_H

#include <QThread>

class threadSynchronisation : public QThread
{
public:
    threadSynchronisation();
    void run();
};

#endif // THREADSYNCHRONISATION_H
