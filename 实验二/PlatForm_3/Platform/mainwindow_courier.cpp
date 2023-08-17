#include "mainwindow_courier.h"
#include "ui_mainwindow_courier.h"

#include <QDebug>
#include <QMessageBox>

MainWindow_Courier::MainWindow_Courier(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_Courier)
{
    ui->setupUi(this);

    // 创建快递员（我）
    QString str = QString(array);
    QStringList strList = str.split(" ");
    curAccount = strList.at(0).toInt();
    person = new Courier(strList.at(0).toInt(), strList.at(1), courier, strList.at(2).toDouble(),
                      strList.at(3),strList.at(4),strList.at(5));

    // 获取所有用户名单
    str = "getUsers";
    qsocket->write(str.toUtf8());
    qsocket->waitForReadyRead();
    array = qsocket->readAll();
    str = QString(array);
    qDebug() << str;
    strList = str.split(" ");
    for(int i=0; i < strList.count(); i++)
        Names.append(strList.at(i));

    // 初始化页面
    setUI();
    setTime();
    // thread for time counts and update
    thread = new MyThread(this);
    connect(thread, &MyThread::refresh, this, &MainWindow_Courier::putTime);
    thread->start();
}

void MainWindow_Courier::refreshDelivery() {
    // 遍历所有按钮并删除
    QLayoutItem *child;
    while ((child = vLayout->takeAt(0)) != 0)
    {
        //setParent为NULL，防止删除之后界面不消失
        if(child->widget())
            child->widget()->setParent(NULL);
        delete child;
    }
    delivery_number.clear();    // 删除所有的记录
    money.clear();
    buttons.clear();

    query.exec("select * from delivery_improve where goodstate = '1' and courier = "+QString::number(curAccount));
    int count = 0;  // 错误计数
    while(query.next()) {
        if(query.value(1).toInt() > Names.size() || query.value(2).toInt() > Names.size()) {
            count ++;
            continue;
        }

        // 显示出来
        QString str = QString::number(query.value(0).toInt());
        str += "  发送方："+Names.at(query.value(1).toInt()-1);
        str += "  接收方："+Names.at(query.value(2).toInt()-1);
        str += "  发送时间："+query.value(3).toString();
        str += "  费用："+QString::number(query.value(6).toDouble(),'f',6);
        str += "  描述："+query.value(8).toString();
        QPushButton *pushBtn = new QPushButton(str);
        pushBtn->setFont(QFont("Consolas",10,75)) ;
        pushBtn->setStyleSheet("background: rgba(255,255,255,75%); color: black") ;
        pushBtn->setAutoExclusive(false);
        pushBtn->setCheckable(true);
        vLayout->addWidget(pushBtn);

        // 记录
        delivery_number.push_back(query.value(0).toInt());
        money.push_back(query.value(6).toDouble());
        buttons.push_back(pushBtn);
    }
    if(count != 0) {
        QMessageBox mess(QMessageBox::Information, QString::number(count)+" errors occured!","user/courier out of range.");
        mess.exec();
    }
}

void MainWindow_Courier::on_pushButton_delivery_clicked()
{
    for(unsigned int i=0; i < delivery_number.size(); i++)
        if(buttons[i]->isChecked()) {
            double curMoney = money[i]/2; // 要转的钱数
            qDebug() << curMoney;
            // 给当前账户
            person->distribute(delivery_number[i], curMoney);
        }
    refreshDelivery();
    QMessageBox mess(QMessageBox::Information,"Success!","Sended successfully.");
    mess.exec();
}

void MainWindow_Courier::on_pushButton_reject_clicked()
{
    for(unsigned int i=0; i < delivery_number.size(); i++)
        if(buttons[i]->isChecked()) {
            person->reject(delivery_number[i]); // 进行拒绝
        }
    refreshDelivery();
    QMessageBox mess(QMessageBox::Information,"Success!","Recjected successfully.");
    mess.exec();
}

void MainWindow_Courier::on_pushButton_refresh_clicked()
{
    refreshDelivery();
    ui->label->setText(QString::number(person->getBalance(), 'f', 6) + " ￥");
}



// _________________________________________________________________________________________________________________
void MainWindow_Courier::setUI() {
    this->setWindowTitle("Courier Page");
    this->setFixedSize(1200, 900) ;
    this->setWindowIcon(QIcon(":/icon/pics/02.jpg")) ;
    this->setAutoFillBackground(true);
    QPalette p = this->palette();
    QPixmap pix(":/background/pics/3.png");
    p.setBrush(QPalette::Window, QBrush(pix));
    this->setPalette(p);

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

    // 新建groupbox
    vLayout = new QVBoxLayout;
    vLayout->setMargin(0);
    vLayout->setSpacing(10);
    ui->groupBox->setLayout(vLayout);   // 将layout弄到groupbox里
    refreshDelivery();

    ui->label->setText(QString::number(person->getBalance(), 'f', 6) + " ￥");
    ui->label->setFont(QFont("Consolas",12,75)) ;
    ui->label->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->pushButton_refresh->setFont(QFont("Consolas",12,75)) ;
    ui->pushButton_refresh->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->pushButton_reject->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->pushButton_reject->setStyleSheet("background: rgba(255,255,255,75%)") ;
    ui->pushButton_delivery->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->pushButton_delivery->setStyleSheet("background: rgba(255,255,255,75%)") ;
}

// ___________________________________________________________________
void MainWindow_Courier::setTime() {
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

void MainWindow_Courier::putTime() {
    line_year->setText(QString::number(system_Time.get_BigTime().get()[0])+"年");
    line_month->setText(QString::number(system_Time.get_BigTime().get()[1])+"月");
    line_day->setText(QString::number(system_Time.get_BigTime().get()[2])+"日");
    line_hour->setText(QString::number(system_Time.get_SmallTime().get()[0])+"时");
    line_minute->setText(QString::number(system_Time.get_SmallTime().get()[1])+"分");
    line_second->setText(QString::number(system_Time.get_SmallTime().get()[2])+"秒");
}

// __________________________________________________________________________________________
MainWindow_Courier::~MainWindow_Courier()
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

    // 删除用户
    delete person;
    person = nullptr;

    // 信息状态归0
    curAccount = 0;

    // 清除记录
    Names.clear();
    CourierNames.clear();
}

void MainWindow_Courier::closeEvent(QCloseEvent *) {
    handle = 0;
    thread->exit();
    emit exit_return();
}
