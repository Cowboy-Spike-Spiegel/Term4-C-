#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_start_clicked();

private:
    Ui::Widget *ui;

    // 协议封装
    QTcpServer* server;
    QTcpSocket* socket;

    // 暂存通信数据，转操作
    QByteArray array;
    // 收到array后进行反馈
    void reply();

    QDir DATAHOME;
};
#endif // WIDGET_H
