#include "mainwindow_administrator.h"
#include "ui_mainwindow_administrator.h"

#include <QDebug>
#include "global.h"

MainWindow_Administrator::MainWindow_Administrator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_Administrator)
{
    ui->setupUi(this);

    // 页面跳转
    connect(ui->action_findDelivery,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->action_findUser,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
        connect(ui->action_show,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(2);
    });

    // 生成所有用户信息和名单
    QDir tempDir(HOME.absolutePath()+"/data");
    QFile tempFile;     // 打开的文件
    QString strAll;     // 全部信息
    QStringList strList;// 分割信息
    QStringList tmpList;// 暂存分割信息
    tempFile.setFileName(tempDir.absolutePath()+"/User");
    if(tempFile.open(QIODevice::ReadOnly)) {
        // 读取并按行分割记录
        strAll = tempFile.readAll();
        strList=strAll.split("\r\n");
        // 逐行分析
        for(int i=0; i<strList.count(); i++) {
            // 分割单行
            tmpList = strList.at(i).split(" ");
            Names.append(tmpList.at(3));    // 生成名单
            User obj(tmpList.at(0).toInt(),tmpList.at(1),user,tmpList.at(2).toDouble(),tmpList.at(3),tmpList.at(4),tmpList.at(5));
            vector_user.push_back(obj);     // 生成用户信息
        }
        // 清理
        strAll.clear();
        strList.clear();
    }
    tempFile.close();

    // 生成所有快递信息
    query.exec("select * from deliverys");
    while(query.next()) {
        Good obj;
        obj.create(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toString(),
                   query.value(4).toString(), query.value(5).toInt(), query.value(6).toDouble(), query.value(7).toString());
        vector_good.push_back(obj);
    }

    // 初始化页面
    setUI();
    setTime();
    // thread for time counts and update
    thread = new MyThread(this);
    connect(thread, &MyThread::refresh, this, &MainWindow_Administrator::putTime);
    thread->start();
}

// 查询快递数据 ***************************************************************************************
void MainWindow_Administrator::refreshFindDelivery() {
    ui->textEdit_findDelivery->document()->setMaximumBlockCount(1000);
    for(unsigned int i=0; i < vector_goodSelect.size(); i++ ) {
        QString number, sender, receiver, time_s, time_r, s, cost;
        number  = QString("%1 ").arg(vector_goodSelect[i].getNumber(),4,10,QLatin1Char(' '));
        sender  = QString("%1 ").arg(Names.at(vector_goodSelect[i].getAccountSender()-1),6,QLatin1Char(' '));
        receiver= QString("%1 ").arg(Names.at(vector_goodSelect[i].getAccountReceiver()-1),6,QLatin1Char(' '));
        time_s  = QString("%1 ").arg(vector_goodSelect[i].getTimeSend(),19,QLatin1Char(' '));
        time_r  = QString("%1 ").arg(vector_goodSelect[i].getTimeReceive(),19,QLatin1Char(' '));
        if(vector_goodSelect[i].getGoodState() == waiting) s = " 等待揽收 ";
        else if(vector_goodSelect[i].getGoodState() == sending) s = " 等待收货 ";
        else if(vector_goodSelect[i].getGoodState() == received) s = " 收货成功 ";
        cost    = QString(" %1  ").arg(QString::number(vector_goodSelect[i].getPrice(),'f',2),5,QLatin1Char(' '));
        ui->textEdit_findDelivery->append(number+sender+receiver+time_s+time_r+s+cost+vector_goodSelect[i].getDiscription());
    }
}

void MainWindow_Administrator::on_pushButton_findDelivery_clicked()
{
    // 准备工作
    vector_goodSelect.clear();
    ui->textEdit_findDelivery->clear();

    if(ui->comboBox_deliverySelect->currentIndex() == -1)
        vector_goodSelect = vector_good;
    // 查询发送方
    else if(ui->comboBox_deliverySelect->currentIndex() == 0) {
        QString input = ui->lineEdit_deliveryInput->text();
        if(input == "") vector_goodSelect = vector_good;
        else
            for(unsigned int i=0; i < vector_good.size(); i++) {
                if(Names.at(vector_good[i].getAccountSender()-1).contains(input))
                    vector_goodSelect.push_back(vector_good[i]);
            }
    }
    // 查询接收方
    else if(ui->comboBox_deliverySelect->currentIndex() == 1) {
        QString input = ui->lineEdit_deliveryInput->text();
        if(input == "") vector_goodSelect = vector_good;
        else
            for(unsigned int i=0; i < vector_good.size(); i++) {
                if(Names.at(vector_good[i].getAccountReceiver()-1).contains(input))
                    vector_goodSelect.push_back(vector_good[i]);
            }
    }
    // 查询时间
    else if(ui->comboBox_deliverySelect->currentIndex() == 2) {
        QString input = ui->lineEdit_deliveryInput->text();
        if(input == "") vector_goodSelect = vector_good;
        else
            for(unsigned int i=0; i < vector_good.size(); i++) {
                if(vector_good[i].getTimeSend().contains(input) || vector_good[i].getTimeReceive().contains(input))
                    vector_goodSelect.push_back(vector_good[i]);
            }
    }
    // 查询单号
    else if(ui->comboBox_deliverySelect->currentIndex() == 3) {
        QString input = ui->lineEdit_deliveryInput->text();
        if(input == "") vector_goodSelect = vector_good;
        else
            for(unsigned int i=0; i < vector_good.size(); i++) {
                if(QString::number(vector_good[i].getNumber()).contains(input))
                    vector_goodSelect.push_back(vector_good[i]);
            }
    }

    // 清除和展示
    ui->comboBox_deliverySelect->setCurrentIndex(-1);
    refreshFindDelivery();
}

// 查询用户页面 ***************************************************************************************
void MainWindow_Administrator::refreshFindUser() {
    ui->textEdit_findUser->document()->setMaximumBlockCount(1000);
    for(unsigned int i=0; i < vector_userSelect.size(); i++ ) {
        ui->textEdit_findUser->append("账号："+QString::number(vector_userSelect[i].getAccount())+" ");
        ui->textEdit_findUser->append("密码："+vector_userSelect[i].getPassword()+" ");
        ui->textEdit_findUser->append("名称："+vector_userSelect[i].getName()+" ");
        ui->textEdit_findUser->append("余额："+QString::number(vector_userSelect[i].getBalance(),'f',6)+" ");
        ui->textEdit_findUser->append("电话："+vector_userSelect[i].getTel()+" ");
        ui->textEdit_findUser->append("地址："+vector_userSelect[i].getAddress()+"\n");
    }
}
void MainWindow_Administrator::on_pushButton_findUser_clicked()
{
    // 准备工作
    vector_userSelect.clear();
    ui->textEdit_findUser->clear();

    QString input = ui->lineEdit_findUser->text();
    qDebug() << "input:" << input;
    if(input == "") vector_userSelect = vector_user;
    else {
        for(unsigned int i=0; i < vector_user.size(); i++) {
            if( QString::number(vector_user[i].getAccount()).contains(input)
                || vector_user[i].getPassword().contains(input)
                || vector_user[i].getName().contains(input)
                || vector_user[i].getTel().contains(input)
                || vector_user[i].getAddress().contains(input)) // 查余额没有任何意义
                vector_userSelect.push_back(vector_user[i]);
        }
    }

    // 展示
    refreshFindUser();
}

void MainWindow_Administrator::refreshShow() {
    // 生成所有用户信息和名单
    QDir tempDir(HOME.absolutePath()+"/data");
    QFile tempFile;     // 打开的文件
    QString strAll;     // 全部信息
    QStringList strList;// 分割信息
    QStringList tmpList;// 暂存分割信息
    tempFile.setFileName(tempDir.absolutePath()+"/Administrator");
    if(tempFile.open(QIODevice::ReadOnly)) {
        // 读取并按行分割记录
        strAll = tempFile.readAll();
        strList=strAll.split("\r\n");
        // 展示第零行
        tmpList = strList.at(0).split(" ");
        ui->label_name->setText(tmpList.at(3));
        ui->label_account->setText(tmpList.at(0));
        ui->label_tel->setText(tmpList.at(4));
        ui->label_balance->setText(QString::number(tmpList.at(2).toDouble(),'f',6));
        strAll.clear();
        strList.clear();
    }
    tempFile.close();
}

// __________________________________________________________________
void MainWindow_Administrator::setUI() {
    this->setWindowTitle("Administrator Page");
    this->setFixedSize(1200, 900) ;
    this->setWindowIcon(QIcon(":/icon/pics/02.jpg")) ;

    // 添加分隔线
    ui->menu_service->addSeparator();
    ui->menu_information->addSeparator();

    line_year = new QLabel(this);
    line_month = new QLabel(this);
    line_day = new QLabel(this);
    line_hour = new QLabel(this);
    line_minute = new QLabel(this);
    line_second = new QLabel(this);
    ui->statusbar->addWidget(line_year);
    ui->statusbar->addWidget(line_month);
    ui->statusbar->addWidget(line_day);
    ui->statusbar->addWidget(line_hour);
    ui->statusbar->addWidget(line_minute);
    ui->statusbar->addWidget(line_second);

    // 展示所有快递信息
    vector_goodSelect = vector_good;
    refreshFindDelivery();
    ui->comboBox_deliverySelect->setCurrentIndex(-1);

    // 展示所有用户信息
    vector_userSelect = vector_user;
    refreshFindUser();

    // 展示系统信息
    refreshShow();

    // 稍微优化一下输出
    ui->textEdit_findDelivery->setFont(QFont("Consolas",10,75)) ;
    ui->textEdit_findDelivery->setStyleSheet("background: rgba(255,255,255,0%)") ;
    ui->textEdit_findUser->setFont(QFont("Consolas",10,75)) ;
    ui->textEdit_findUser->setStyleSheet("background: rgba(255,255,255,0%)") ;
}









// ___________________________________________________________________
void MainWindow_Administrator::setTime() {
    QDir tempDir(HOME.absolutePath()+"/Logs");
    if(!tempDir.exists()) {
        qDebug()<<"不存在该路径";
        tempDir.mkpath(HOME.absolutePath()+"/Logs");
    }

    QFile tempFile(tempDir.absolutePath()+"/time.log");
    if(tempFile.open(QIODevice::ReadOnly)) {
        // 录入数据
        QByteArray array = tempFile.readAll();
        char* str = array.data();
        std::vector<int> obj ;
        for( int i=0; i < array.length() ; i++ ) {
            int tmp=0;
            while(str[i]!=' ' && str[i]!='\n' && i < array.length())
                tmp = tmp*10+(str[i++]-'0');
            obj.push_back(tmp);
        }

        // 数据数量或内容不合法，删除重开
        if(obj.size()!=8 || !system_Time.create(obj[0], obj[1], obj[2], obj[3], obj[4], obj[5], obj[6], obj[7])) {
            tempFile.close();
            tempFile.remove();
            tempFile.open(QIODevice::WriteOnly);
            tempFile.write(QString("2022 2 28 0 0 0 1\n").toUtf8());
            system_Time.create(2022, 2, 28, 0, 0, 0, 1, 1);
        }
    }
    else {
        qDebug()<<"File ERROR!";
        tempFile.close();
        tempFile.open(QIODevice::WriteOnly);
        tempFile.write(QString("2022 2 28 0 0 0 1\n").toUtf8());
        system_Time.create(2022, 2, 28, 0, 0, 0, 1, 1);
    }
    tempFile.close();
}

void MainWindow_Administrator::putTime() {
    line_year->setText(QString::number(system_Time.get_BigTime().get()[0])+"年");
    line_month->setText(QString::number(system_Time.get_BigTime().get()[1])+"月");
    line_day->setText(QString::number(system_Time.get_BigTime().get()[2])+"日");
    line_hour->setText(QString::number(system_Time.get_SmallTime().get()[0])+"时");
    line_minute->setText(QString::number(system_Time.get_SmallTime().get()[1])+"分");
    line_second->setText(QString::number(system_Time.get_SmallTime().get()[2])+"秒");
}

// __________________________________________________________________________________________
MainWindow_Administrator::~MainWindow_Administrator()
{
    delete line_year;
    delete line_month;
    delete line_day;
    delete line_hour;
    delete line_minute;
    delete line_second;

    delete ui;
    delete thread;
    thread = NULL;

    QFile tempFile(HOME.absolutePath()+"/Logs/time.log");
    tempFile.remove();
    tempFile.open(QIODevice::WriteOnly);
    QString str = QString::number(system_Time.get_BigTime().get()[0]);
    str += " " + QString::number(system_Time.get_BigTime().get()[1]);
    str += " " + QString::number(system_Time.get_BigTime().get()[2]);
    str += " " + QString::number(system_Time.get_SmallTime().get()[0]);
    str += " " + QString::number(system_Time.get_SmallTime().get()[1]);
    str += " " + QString::number(system_Time.get_SmallTime().get()[2]);
    str += " " + QString::number(system_Time.get_DayOfWeek());
    str += " " + QString::number(system_Time.get_Week());
    tempFile.write(str.toUtf8());
    tempFile.close();
    qDebug() << str;

    // 账号数据归0
    curAccount = 0;
}

void MainWindow_Administrator::closeEvent(QCloseEvent *) {
    handle = 0;
    thread->exit();
    emit exit_return();
}
