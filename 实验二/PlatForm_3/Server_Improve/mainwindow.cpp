#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTcpSocket>
#include "serverthread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_port->setText("8848");

    // 创建父对象使该窗口释放内存(服务端)
    qserver = new QTcpServer(this);
    connection_cnt = 0; // 对于connection，进行计数

    // 对每个新连接，创建一个线程去处理
    connect(qserver, &QTcpServer::newConnection, this, [=](){
        connection_cnt++;
        ui->textEdit_record->append("");
        ui->textEdit_record->append("-------------------------------------");
        ui->textEdit_record->append("Socket connected.");
        ui->textEdit_record->append(QString::number(connection_cnt)+" sockets has been connected.");
        ui->textEdit_record->append("");

        QTcpSocket* qsocket = qserver->nextPendingConnection();
        // 给线程传参处理
        ServerThread* subThread = new ServerThread(qsocket);
        subThread->start();

        // 关闭时析构线程 **********************************
        connect(subThread, &ServerThread::exit_return, this, [=](){
            connection_cnt--;
            ui->textEdit_record->append("Socket disconnected.");
            ui->textEdit_record->append("-------------------------------------");
            ui->textEdit_record->append(QString::number(connection_cnt)+" sockets has been connected.");
            ui->textEdit_record->append("");
            subThread->exit();
            subThread->wait();
            subThread->deleteLater();
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_setListen_clicked()
{
    // 启动监听服务
    unsigned port = ui->lineEdit_port->text().toUShort();
    ui->label_port->clear();
    if(port == 0) {
        ui->textEdit_record->append("Input invalid.");
        return;
    }

    qserver->listen(QHostAddress::Any, port);
    ui->pushButton_setListen->setDisabled(true);
    ui->textEdit_record->append("Server started.");
    ui->textEdit_record->append("");
}
