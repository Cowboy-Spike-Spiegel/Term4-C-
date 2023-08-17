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

    ui->pushButton->setFont(QFont("Microsoft YaHei",20,75)) ;
    ui->pushButton->setStyleSheet("background: rgba(255,255,255,50%)") ;
}

void SignUp::on_pushButton_clicked()
{
    QString name    = ui->lineEdit_name->text();
    QString password= ui->lineEdit_password->text();
    QString tel     = ui->lineEdit_tel->text();
    QString address = ui->lineEdit_address->text();

    if(name.contains(" ") || password.contains(" ") || tel.contains(" ") || address.contains(" ")) {
        QMessageBox mess(QMessageBox::Information,"Warning!","No space you input.");
        mess.exec();
        return;
    } else if(!tel.isEmpty() && tel.length() != 11) {
        QMessageBox mess(QMessageBox::Information,"Warning!","Tel.len should be 11.");
        mess.exec();
        return;
    }

    if(name != "" && password != "" && tel.length() == 11 && address != "") {
        QDir tempDir(HOME.absolutePath()+"/data");
        QFile tempFile(tempDir.absolutePath()+"/User");     // 打开的文件
        if(tempFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
            // 获取注册账号
            QString strAll = tempFile.readAll();
            qDebug() << strAll;
            int count = 1;  // 一共多少条记录
            for(int i=0; i < strAll.size(); i++)
                if(strAll[i] == '\n') count++;

            QTextStream output(&tempFile);   // 打开文件流并写入
            output.setCodec(QTextCodec::codecForName("utf-8"));
            // 没有用户
            if(strAll == "") {
                output << QString::number(1)+" "+password+" 0.000000 "+name+" "+tel+" "+address;
                count = 0;
            } else
                output << "\n"+QString::number(count+1)+" "+password+" 0.000000 "+name+" "+tel+" "+address;
            curAccount = count+1;

            QMessageBox mess(QMessageBox::Information,"Success!","Your account is: "+QString::number(count+1));
            mess.exec();

            this->close();
        }
        else
            qDebug()<<"User File ERROR!";
        tempFile.close();
    } else {
        QMessageBox mess(QMessageBox::Information,"Warning!","Invalid Input! Not empty and tel.len = 11.");
        mess.exec();
    }
}

