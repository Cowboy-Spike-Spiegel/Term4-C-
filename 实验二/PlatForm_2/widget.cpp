#include "widget.h"
#include "ui_widget.h"

#include <QCoreApplication>
#include <QMessageBox>
#include <QDebug>
#include "global.h"
#include "people.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setUI();

    // 初始化
    setHOMEPath();
    linkDatabase();
    curAccount = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setUI() {
    this->setWindowTitle("Welcome!");
    this->setFixedSize(600, 200) ;
    this->setWindowIcon(QIcon(":/icon/pics/02.jpg")) ;
    this->setAutoFillBackground(true);
    QPalette p = this->palette();
    QPixmap pix(":/background/pics/4.png");
    p.setBrush(QPalette::Window, QBrush(pix));
    this->setPalette(p);

    ui->label_account->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->label_account->setStyleSheet("background: rgba(255,255,255,0%)") ;
    ui->label_password->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->label_password->setStyleSheet("background: rgba(255,255,255,0%)") ;
    ui->lineEdit_account->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->lineEdit_account->setStyleSheet("background: rgba(255,255,255,0%);color:white") ;
    ui->lineEdit_password->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->lineEdit_password->setStyleSheet("background: rgba(255,255,255,0%);color:white") ;

    ui->pushButton_signinAsUser->setFont(QFont("Microsoft YaHei",10,75)) ;
    ui->pushButton_signinAsUser->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->pushButton_signinAsCourier->setFont(QFont("Microsoft YaHei",10,75)) ;
    ui->pushButton_signinAsCourier->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->pushButton_signinAsAdmin->setFont(QFont("Microsoft YaHei",10,75)) ;
    ui->pushButton_signinAsAdmin->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->pushButton_signup->setFont(QFont("Microsoft YaHei",10,75)) ;
    ui->pushButton_signup->setStyleSheet("background: rgba(255,255,255,50%)") ;
}


// ______________________________________________________________________________________________________
void Widget::setHOMEPath() {
    // initialize
    HOME.setPath(QCoreApplication::applicationDirPath());

    // 打开配置信息文件夹
    QDir tempDir(HOME.absolutePath()+"/data");
    if(!tempDir.exists()) {
        qDebug()<<"不存在该路径";
        QMessageBox mess(QMessageBox::Information,"Warning","Event: User File missed!");
        mess.exec();
    }
}

void Widget::linkDatabase() {
    // 连接数据库
    if (QSqlDatabase::contains("QMYSQL")) {
        db = QSqlDatabase::database("QMYSQL");
    } else {
        db = QSqlDatabase::addDatabase("QMYSQL");
    }
    db.setHostName("localhost");
    db.setPort(3306);
    //db.setHostName("ngrok2.xiaomiqiu.cn");
    //db.setPort(34666);
    db.setUserName("user_cpp");
    db.setPassword("password");
    db.setDatabaseName("project_cpp");

    if (db.open()){
        qDebug()<<"database success";
    }
    else {
        QMessageBox mess(QMessageBox::Information,"Warning!","database fail!");
        mess.exec();
    }
}

// _____________________________________________________________________________________________________
void Widget::on_pushButton_signinAsUser_clicked()
{
    QDir tempDir(HOME.absolutePath()+"/data");
    QFile tempFile;     // 打开的文件
    QString strAll;     // 全部信息
    QStringList strList;// 分割信息
    QStringList tmpList;// 暂存分割信息

    int         account = ui->lineEdit_account->text().toInt();
    QString     password= ui->lineEdit_password->text();

    // 登录用户 ________________________________________________________________________________
    tempFile.setFileName(tempDir.absolutePath()+"/User");
    if(tempFile.open(QIODevice::ReadOnly)) {
        // 读取并按行分割记录
        strAll = tempFile.readAll();
        strList=strAll.split("\r\n");
        // 逐行分析
        for(int i=0; i<strList.count(); i++) {
            // 分割单行
            tmpList = strList.at(i).split(" ");
            if(account == tmpList.at(0).toInt() && password == tmpList.at(1)) {
                // 登陆成功
                qDebug() << "login success: User";
                curAccount = account;
                break;
            }
        }
        // 清理
        strAll.clear();
        strList.clear();
    }
    else
        qDebug()<<"User File ERROR!";
    tempFile.close();

    if(curAccount != 0) {
        ui->lineEdit_account->clear();
        ui->lineEdit_password->clear();
        // 开用户界面
        this->userPage = new MainWindow ;
        connect(userPage, &MainWindow::exit_return, [=](){
            curAccount = 0;
            delete userPage;    // 关闭并返回
            userPage = nullptr;
            this->show();
        });
        userPage->show() ;
        this->close();
    } else {
        QMessageBox mess(QMessageBox::Information,"Warning!","Authentic fail!");
        mess.exec();
    }
}

void Widget::on_pushButton_signinAsCourier_clicked()
{
    QDir tempDir(HOME.absolutePath()+"/data");
    QFile tempFile;     // 打开的文件
    QString strAll;     // 全部信息
    QStringList strList;// 分割信息
    QStringList tmpList;// 暂存分割信息

    int         account = ui->lineEdit_account->text().toInt();
    QString     password= ui->lineEdit_password->text();

    // 登录快递员 ________________________________________________________________________________
    tempFile.setFileName(tempDir.absolutePath()+"/Courier");
    if(tempFile.open(QIODevice::ReadOnly)) {
        // 读取并按行分割记录
        strAll = tempFile.readAll();
        strList=strAll.split("\r\n");
        // 逐行分析
        for(int i=0; i<strList.count(); i++) {
            // 分割单行
            tmpList = strList.at(i).split(" ");
            if(account == tmpList.at(0).toInt() && password == tmpList.at(1)) {
                // 登陆成功
                qDebug() << "login success: Courier";
                curAccount = account;
                break;
            }
        }
        // 清理
        strAll.clear();
        strList.clear();
    }
    else
        qDebug()<<"User File ERROR!";
    tempFile.close();

    if(curAccount != 0) {
        ui->lineEdit_account->clear();
        ui->lineEdit_password->clear();
        // 开快递员界面
        this->courierPage = new MainWindow_Courier ;
        connect(courierPage, &MainWindow_Courier::exit_return, [=](){
            curAccount = 0;
            delete courierPage;    // 关闭并返回
            courierPage = nullptr;
            this->show();
        });
        courierPage->show() ;
        this->close();
    } else {
        QMessageBox mess(QMessageBox::Information,"Warning!","Authentic fail!");
        mess.exec();
    }
}


void Widget::on_pushButton_signinAsAdmin_clicked()
{
    QDir tempDir(HOME.absolutePath()+"/data");
    QFile tempFile;     // 打开的文件
    QString strAll;     // 全部信息
    QStringList strList;// 分割信息
    QStringList tmpList;// 暂存分割信息

    int         account = ui->lineEdit_account->text().toInt();
    QString     password= ui->lineEdit_password->text();

    // 优先登录管理员 _________________________________________________________________________
    tempFile.setFileName(tempDir.absolutePath()+"/Administrator");
    if(tempFile.open(QIODevice::ReadOnly)) {
        // 读取并按行分割记录
        strAll = tempFile.readAll();
        strList=strAll.split("\r\n");
        // 逐行分析
        for(int i=0; i < strList.count(); i++) {
            // 分割单行
            tmpList = strList.at(i).split(" ");
            if(account == tmpList.at(0).toInt() && password == tmpList.at(1)) {
                // 登陆成功
                qDebug() << "login success: Administrator";
                curAccount = account;
                break;
            }
        }
        // 清理
        strAll.clear();
        strList.clear();
    }
    else
        qDebug()<<"Administrator File ERROR!";
    tempFile.close();

    if(curAccount != 0) {
        ui->lineEdit_account->clear();
        ui->lineEdit_password->clear();
        // 开管理员界面
        this->administratorPage = new MainWindow_Administrator ;
        connect(administratorPage, &MainWindow_Administrator::exit_return, [=](){
            curAccount = 0;
            delete administratorPage;    // 关闭并返回
            administratorPage = nullptr;
            this->show();
        });
        administratorPage->show() ;
        this->close();
    } else {
        QMessageBox mess(QMessageBox::Information,"Warning!","Authentic fail!");
        mess.exec();
    }
}


void Widget::on_pushButton_signup_clicked()
{
    this->sign = new SignUp ;
    // close MainPage and show this
    connect(sign, &SignUp::exit_return, [=](){
        // 自动显示刚注册的账号
        if(curAccount != 0)
            ui->lineEdit_account->setText(QString::number(curAccount));
        delete sign;
        sign = nullptr;
        this->show();
    });

    sign->show() ;
    this->close();
}


void Widget::on_lineEdit_password_returnPressed()
{
    // 默认登录用户
    on_pushButton_signinAsUser_clicked();
}

