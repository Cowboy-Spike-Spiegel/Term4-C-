#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDir>
#include <QFile>

class ServerThread : public QThread
{
    Q_OBJECT
public:
    explicit ServerThread(QTcpSocket* qsocket, QObject *parent = nullptr);

protected:
    void run() override;

private:
    QDir DATAHOME;
    QTcpSocket* threadSocket;
    QByteArray array;   // 记录传输信息

    void reply();   // 针对array进行服务

signals:
    void exit_return();
};

#endif // SERVERTHREAD_H
