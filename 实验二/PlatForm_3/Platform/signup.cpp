#include "signup.h"
#include "ui_signup.h"

#include <QTextCodec>
#include <QIcon>
#include <QMessageBox>
#include <QDebug>
#include "global.h"

SignUp::SignUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
    setUI();
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::closeEvent(QCloseEvent *) {
    emit exit_return();
}

void SignUp::setUI() {
    this->setWindowTitle("Sign up");
    this->setFixedSize(400, 300) ;
    this->setWindowIcon(QIcon(":/icon/pics/02.jpg")) ;
    this->setAutoFillBackground(true);
    QPalette p = this->palette();
    QPixmap pix(":/background/pics/2.png");
    p.setBrush(QPalette::Window, QBrush(pix));
    this->setPalette(p);

    ui->label_name->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->label_name->setStyleSheet("background: rgba(255,255,255,0%);color:white") ;
    ui->label_password->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->label_password->setStyleSheet("background: rgba(255,255,255,0%);color:white") ;
    ui->label_tel->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->label_tel->setStyleSheet("background: rgba(255,255,255,0%);color:white") ;
    ui->label_address->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->label_address->setStyleSheet("background: rgba(255,255,255,0%);color:white") ;
    ui->lineEdit_name->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->lineEdit_name->setStyleSheet("background: rgba(255,255,255,50%);color:white") ;
    ui->lineEdit_password->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->lineEdit_password->setStyleSheet("background: rgba(255,255,255,50%);color:white") ;
    ui->lineEdit_tel->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->lineEdit_tel->setStyleSheet("background: rgba(255,255,255,50%);color:white") ;
    ui->lineEdit_address->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->lineEdit_address->setStyleSheet("background: rgba(255,255,255,50%);color:white") ;

    ui->pushButton_user->setFont(QFont("Consolas",10,75)) ;
    ui->pushButton_user->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->pushButton_courier->setFont(QFont("Consolas",10,75)) ;
    ui->pushButton_courier->setStyleSheet("background: rgba(255,255,255,50%)") ;
}

void SignUp::on_pushButton_user_clicked()
{
    QString name    = ui->lineEdit_name->text();
    QString password= ui->lineEdit_password->text();
    QString tel     = ui->lineEdit_tel->text();
    QString address = ui->lineEdit_address->text();

    if(name.contains(" ") || name.isEmpty() || password.contains(" ") || password.isEmpty() ||
        tel.contains(" ") || tel.isEmpty() ||  address.contains(" ") || address.isEmpty()) {
        QMessageBox mess(QMessageBox::Information,"Warning!","No space, or empty you input.");
        mess.exec();
        return;
    } else if(tel.length() != 11) {
        QMessageBox mess(QMessageBox::Information,"Warning!","Tel.len should be 11.");
        mess.exec();
        return;
    }

    // socket 通信 *****************************************************************
    QString str = "user_insert " + name + " " + password + " " + tel + " " + address;
    qsocket->write(str.toUtf8());
    qsocket->waitForReadyRead();
    array = qsocket->readAll();
    str = QString(array);
    qDebug() << str;

    curAccount = str.toInt();
    QMessageBox mess(QMessageBox::Information,"Success!","Your account is: "+QString::number(curAccount));
    mess.exec();
}


void SignUp::on_pushButton_courier_clicked()
{
    QString name    = ui->lineEdit_name->text();
    QString password= ui->lineEdit_password->text();
    QString tel     = ui->lineEdit_tel->text();
    QString address = ui->lineEdit_address->text();

    if(name.contains(" ") || name.isEmpty() || password.contains(" ") || password.isEmpty() ||
        tel.contains(" ") || tel.isEmpty() ||  address.contains(" ") || address.isEmpty()) {
        QMessageBox mess(QMessageBox::Information,"Warning!","No space, or empty you input.");
        mess.exec();
        return;
    } else if(tel.length() != 11) {
        QMessageBox mess(QMessageBox::Information,"Warning!","Tel.len should be 11.");
        mess.exec();
        return;
    }

    // socket 通信 *****************************************************************
    QString str = "courier_insert " + name + " " + password + " " + tel + " " + address;
    qsocket->write(str.toUtf8());
    qsocket->waitForReadyRead();
    array = qsocket->readAll();
    str = QString(array);
    qDebug() << str;

    curAccount = str.toInt();
    QMessageBox mess(QMessageBox::Information,"Success!","Your account is: "+QString::number(curAccount));
    mess.exec();
}

