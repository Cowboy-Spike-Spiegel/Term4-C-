#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

// Thread for timer update, run with return signal isDone
class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);

protected:
    void run();

signals:
    void refresh();
};

#endif // MYTHREAD_H
