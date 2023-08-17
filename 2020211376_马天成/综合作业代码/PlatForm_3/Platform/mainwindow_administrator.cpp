#include "mainwindow_administrator.h"
#include "ui_mainwindow_administrator.h"

#include <QDebug>
#include <QMessageBox>


MainWindow_Administrator::MainWindow_Administrator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_Administrator)
{
    ui->setupUi(this);

    // 创建管理员（我）
    QString str = QString(array);
    QStringList strList = str.split(" ");
    curAccount = strList.at(0).toInt();
    person = new Administrator(strList.at(0).toInt(), strList.at(1), administrator,
                              strList.at(2).toDouble(), strList.at(3),strList.at(4));

    // 生成所有用户信息和快捷名单
    str = "admin_findUsers";
    qsocket->write(str.toUtf8());
    qsocket->waitForReadyRead();
    array = qsocket->readAll();
    str = QString(array);
    qDebug() << str;
    strList = str.split("|");
    for(int i=0; i < strList.count(); i++) {
        QStringList tmpList = strList.at(i).split(" ");
        Names.append(tmpList.at(3));
        User obj(tmpList.at(0).toInt(),tmpList.at(1),user,tmpList.at(2).toDouble(),tmpList.at(3),tmpList.at(4),tmpList.at(5));
        vector_user.push_back(obj);     // 生成用户信息
    }

    // 创建快递员名单，顺便将名单填进候选框
    str = "getCouriers";
    qsocket->write(str.toUtf8());
    qsocket->waitForReadyRead();
    array = qsocket->readAll();
    str = QString(array);
    qDebug() << str;
    strList = str.split(" ");
    for(int i=0; i < strList.count(); i++) {
        CourierNames.append(strList.at(i));
        ui->comboBox_courier->addItem(strList.at(i));
    }

    // 生成所有快递信息
    query.exec("select * from delivery_improve");
    int count = 0;
    while(query.next()) {
        // 错误记录，直接跳过
        if(query.value(1).toInt() > Names.size() || query.value(2).toInt() > Names.size() || query.value(9).toInt() > CourierNames.size()) {
            count++;
            continue;
        }
        // 易碎品
        if(query.value(6).toInt() == 8*query.value(5).toInt()) {
            Good* obj = new Good_Fragile;
            obj->create(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toString(), query.value(4).toString(),
                        query.value(5).toInt(), query.value(7).toInt(), query.value(8).toString(), query.value(9).toInt());
            vector_good.push_back(obj);
        }
        // 图书
        else if(query.value(6).toInt() == 2*query.value(5).toInt()) {
            Good* obj = new Good_Book;
            obj->create(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toString(), query.value(4).toString(),
                        query.value(5).toInt(), query.value(7).toInt(), query.value(8).toString(), query.value(9).toInt());
            vector_good.push_back(obj);
        }
        // 普通快递
        else if(query.value(6).toInt() == 5*query.value(5).toInt()) {
            Good* obj = new Good_Normal;
            obj->create(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toString(), query.value(4).toString(),
                        query.value(5).toInt(), query.value(7).toInt(), query.value(8).toString(), query.value(9).toInt());
            vector_good.push_back(obj);
        }
    }
    // 报错
    if(count > 0) {
        QMessageBox mess(QMessageBox::Information, QString::number(count)+" errors occured!","In findAll:user/courier number out of range.");
        mess.exec();
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

    // 错误计数
    for(unsigned int i=0; i < vector_goodSelect.size(); i++ ) {

        QString number, sender, receiver, time_s, time_r, s, cost, courier;
        number  = QString("%1 ").arg(vector_goodSelect[i]->getNumber(),4,10,QLatin1Char(' '));
        sender  = QString("%1 ").arg(Names.at(vector_goodSelect[i]->getAccountSender()-1),6,QLatin1Char(' '));
        receiver= QString("%1 ").arg(Names.at(vector_goodSelect[i]->getAccountReceiver()-1),6,QLatin1Char(' '));
        time_s  = QString("%1 ").arg(vector_goodSelect[i]->getTimeSend(),19,QLatin1Char(' '));
        time_r  = QString("%1 ").arg(vector_goodSelect[i]->getTimeReceive(),19,QLatin1Char(' '));
        if(vector_goodSelect[i]->getGoodState() == waiting) s = " 等待揽收 ";
        else if(vector_goodSelect[i]->getGoodState() == sending) s = " 等待收货 ";
        else if(vector_goodSelect[i]->getGoodState() == received) s = " 收货成功 ";
        cost    = QString(" %1  ")
                .arg(QString::number(vector_goodSelect[i]->getPrice()*vector_goodSelect[i]->getWeight(),'f',2),5,QLatin1Char(' '));
        if(vector_goodSelect[i]->getCoutier() != 0)
            courier = QString("%1 ").arg(CourierNames.at(vector_goodSelect[i]->getCoutier()-1),6,QLatin1Char(' '));
        else    courier = "            ";

        ui->textEdit_findDelivery->append(number+sender+receiver+time_s+time_r+s+cost+courier+vector_goodSelect[i]->getDiscription());
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
                if(Names.at(vector_good[i]->getAccountSender()-1).contains(input))
                    vector_goodSelect.push_back(vector_good[i]);
            }
    }
    // 查询接收方
    else if(ui->comboBox_deliverySelect->currentIndex() == 1) {
        QString input = ui->lineEdit_deliveryInput->text();
        if(input == "") vector_goodSelect = vector_good;
        else
            for(unsigned int i=0; i < vector_good.size(); i++) {
                if(Names.at(vector_good[i]->getAccountReceiver()-1).contains(input))
                    vector_goodSelect.push_back(vector_good[i]);
            }
    }
    // 查询时间
    else if(ui->comboBox_deliverySelect->currentIndex() == 2) {
        QString input = ui->lineEdit_deliveryInput->text();
        if(input == "") vector_goodSelect = vector_good;
        else
            for(unsigned int i=0; i < vector_good.size(); i++) {
                if(vector_good[i]->getTimeSend().contains(input) || vector_good[i]->getTimeReceive().contains(input))
                    vector_goodSelect.push_back(vector_good[i]);
            }
    }
    // 查询单号
    else if(ui->comboBox_deliverySelect->currentIndex() == 3) {
        QString input = ui->lineEdit_deliveryInput->text();
        if(input == "") vector_goodSelect = vector_good;
        else
            for(unsigned int i=0; i < vector_good.size(); i++) {
                if(QString::number(vector_good[i]->getNumber()).contains(input))
                    vector_goodSelect.push_back(vector_good[i]);
            }
    }

    // 清除和展示
    ui->comboBox_deliverySelect->setCurrentIndex(-1);
    refreshFindDelivery();
}

void MainWindow_Administrator::on_pushButton_findRefresh_clicked()
{
    for(unsigned int i=0; i < vector_good.size(); i++) {
        delete vector_good[i];
        vector_good[i] = nullptr;
    }
    vector_good.clear();
    // 生成所有快递信息

    int count = 0;
    query.exec("select * from delivery_improve");
    while(query.next()) {
        if(query.value(1).toInt() > Names.size() || query.value(2).toInt() > Names.size() || query.value(9).toInt() > CourierNames.size()) {
            count++;
            continue;
        }
        // 易碎品
        if(query.value(6).toInt() == 8*query.value(5).toInt()) {
            Good* obj = new Good_Fragile;
            obj->create(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toString(), query.value(4).toString(),
                        query.value(5).toInt(), query.value(7).toInt(), query.value(8).toString(), query.value(9).toInt());
            vector_good.push_back(obj);
        }
        // 图书
        else if(query.value(6).toInt() == 2*query.value(5).toInt()) {
            Good* obj = new Good_Book;
            obj->create(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toString(), query.value(4).toString(),
                        query.value(5).toInt(), query.value(7).toInt(), query.value(8).toString(), query.value(9).toInt());
            vector_good.push_back(obj);
        }
        // 普通快递
        else if(query.value(6).toInt() == 5*query.value(5).toInt()) {
            Good* obj = new Good_Normal;
            obj->create(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toString(), query.value(4).toString(),
                        query.value(5).toInt(), query.value(7).toInt(), query.value(8).toString(), query.value(9).toInt());
            vector_good.push_back(obj);
        }
    }
    // 报错
    if(count > 0) {
        QMessageBox mess(QMessageBox::Information, QString::number(count)+" errors occured!","user/courier out of range.");
        mess.exec();
    }

    // 刷新页面
    vector_goodSelect = vector_good;
    ui->textEdit_findDelivery->clear();
    refreshFindDelivery();
}


// 查询用户页面 ***************************************************************************************
void MainWindow_Administrator::refreshFindUser() {
    ui->textEdit_findUser->document()->setMaximumBlockCount(100);
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


// 刷新所有已分配快递并回收*********************************************************************************
void MainWindow_Administrator::startRecycle() {
    int month = system_Time.get_BigTime().get()[1];
    int day = system_Time.get_BigTime().get()[2];
    query.exec("select * from delivery_improve");
    while(query.next()) {
        // 假如已分配派送但是没有送货
        if(query.value(7).toInt() == 1) {
            QString tmpTime = query.value(3).toString();
            // 至少一天时间过了，还没派送，回收快递
            if(tmpTime.split('-').at(1).toInt() < month || tmpTime.split('-').at(2).toInt() < day )
                recycleExpress(query.value(0).toInt());
        }
    }
}
void MainWindow_Administrator::recycleExpress(int number) {
    QSqlQuery tmpQuery;
    tmpQuery.exec("update delivery_improve set goodstate = '0', courier = 0 where number = "+QString::number(number));
}


// 快递员删除机制（输入快递员唯一标识）*************************************************************************
void MainWindow_Administrator::on_pushButton_delete_clicked()
{
    if(ui->comboBox_courier->currentIndex() == -1) {
        QMessageBox mess(QMessageBox::Information,"Error!","No courier selected.");
        mess.exec();
    }
    else{
        int number = ui->comboBox_courier->currentIndex()+1;
        QString name = ui->comboBox_courier->currentText();
        if(name.contains("(deleted)")) {
            QMessageBox mess(QMessageBox::Information,"Error!","Courier has been deleted.");
            mess.exec();
            return ;
        }
        // 删除用户
        qDebug() << number;
        deleteCarrier(number);
    }
    ui->comboBox_courier->setCurrentIndex(-1);
}
void MainWindow_Administrator::deleteCarrier(int number) {
    std::vector<int> obj;
    query.exec("select * from delivery_improve where goodstate = '1' and courier = "+QString::number(number));
    qDebug() << "select * from delivery_improve where goodstate = '1' and courier = "+QString::number(number);
    while(query.next())
        obj.push_back(query.value(0).toInt());

    // 回收未发送快递
    if(obj.size() != 0) {
        QMessageBox msgBox;
        msgBox.setText("提示:此快递员有未配送快递");
        msgBox.setInformativeText("确实要删除吗?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Ok){
            // 回收所有快递
            for(int i=0; i < (int)obj.size(); i++)
                recycleExpress(obj[i]);
        }
        else return;
    }

    // 调用管理员身份进行处理，删除账号（名字里面加个串）
    person->deleteCourier(number);
}



// 快递分配 ******************************************************************************************
void MainWindow_Administrator::refreshAllocate() {
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
    buttons.clear();

    query.exec("select * from delivery_improve where goodstate = '0'");
    int count = 0;
    while(query.next()) {
        if(query.value(1).toInt() > Names.size() || query.value(2).toInt() > Names.size() || query.value(9).toInt() > CourierNames.size()) {
            count++;
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
        buttons.push_back(pushBtn);
    }
    if(count != 0) {
        QMessageBox mess(QMessageBox::Information, QString::number(count)+" errors occured!","In allocate:user/courier out of range.");
        mess.exec();
    }

    ui->comboBox_courier->setCurrentIndex(-1);
}

void MainWindow_Administrator::on_pushButton_allocate_clicked()
{
    int courierIndex = ui->comboBox_courier->currentIndex();
    if(courierIndex == -1) {
        QMessageBox mess(QMessageBox::Information,"Warning!","No courier selected.");
        mess.exec();
        return;
    }

    // 假如这个已经被删除
    if(ui->comboBox_courier->currentText().contains("(deleted)")) {
        QMessageBox mess(QMessageBox::Information,"Warning!","Courier not exist.");
        mess.exec();
        return;
    }

    for(unsigned int i=0; i < delivery_number.size(); i++)
        if(buttons[i]->isChecked()) {
            query.exec("update delivery_improve set goodstate = '1', courier = "+QString::number(courierIndex+1)
                       +" where number = "+QString::number(delivery_number[i]));
        }
    refreshAllocate();
    QMessageBox mess(QMessageBox::Information,"Success!","Delivery to "+CourierNames.at(courierIndex)+" successfully.");
    mess.exec();
}

// 系统信息展示 **********************************************************
void MainWindow_Administrator::refreshShow() {
    ui->label_name->setText(person->getName());
    ui->label_account->setText(QString::number(person->getAccount()));
    ui->label_tel->setText(person->getTel());
    ui->label_balance->setText(QString::number(person->getBalance(),'f',6));
}

void MainWindow_Administrator::on_pushButton_refreshShow_clicked()
{
    refreshShow();
}


// __________________________________________________________________
void MainWindow_Administrator::setUI() {
    this->setWindowTitle("Administrator Page");
    this->setFixedSize(1200, 900) ;
    this->setWindowIcon(QIcon(":/icon/pics/02.jpg")) ;

    // 页面跳转
    connect(ui->action_findDelivery,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->action_findUser,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->action_allocate,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(2);
    });
    connect(ui->action_show,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(3);
    });

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
    ui->comboBox_deliverySelect->setFont(QFont("Consolas",12,75)) ;
    ui->comboBox_deliverySelect->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->lineEdit_deliveryInput->setFont(QFont("Consolas",12,75)) ;
    ui->lineEdit_deliveryInput->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->pushButton_findDelivery->setFont(QFont("Consolas",12,75)) ;
    ui->pushButton_findDelivery->setStyleSheet("background: rgba(180,235,255,75%)") ;
    ui->pushButton_findRefresh->setFont(QFont("Consolas",12,75)) ;
    ui->pushButton_findRefresh->setStyleSheet("background: rgba(255,255,255,50%)") ;

    // 展示所有用户信息
    vector_userSelect = vector_user;
    ui->lineEdit_findUser->setFont(QFont("Consolas",12,75)) ;
    ui->lineEdit_findUser->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->pushButton_findUser->setFont(QFont("Consolas",12,75)) ;
    ui->pushButton_findUser->setStyleSheet("background: rgba(255,255,255,50%)") ;
    refreshFindUser();

    // 分配信息
    vLayout = new QVBoxLayout;
    vLayout->setMargin(0);
    vLayout->setSpacing(10);
    ui->groupBox->setLayout(vLayout);
    ui->comboBox_courier->setCurrentIndex(-1);
    refreshAllocate();
    ui->comboBox_courier->setFont(QFont("Consolas",12,75)) ;
    ui->comboBox_courier->setStyleSheet("background: rgba(180,235,255,75%)") ;
    ui->pushButton_allocate->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->pushButton_allocate->setStyleSheet("background: rgba(180,235,255,75%)") ;

    // 展示系统信息
    refreshShow();
    ui->label_account->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->label_account->setStyleSheet("background: rgba(180,235,255,75%)") ;
    ui->label_name->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->label_name->setStyleSheet("background: rgba(180,235,255,75%)") ;
    ui->label_tel->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->label_tel->setStyleSheet("background: rgba(180,235,255,75%)") ;
    ui->label_balance->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->label_balance->setStyleSheet("background: rgba(180,235,255,75%)") ;

    // 稍微优化一下输出
    ui->textEdit_findDelivery->setFont(QFont("Consolas",10,75)) ;
    ui->textEdit_findDelivery->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->textEdit_findUser->setFont(QFont("Consolas",10,75)) ;
    ui->textEdit_findUser->setStyleSheet("background: rgba(255,255,255,50%)") ;
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
    delete vLayout;

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

void MainWindow_Administrator::closeEvent(QCloseEvent *) {
    handle = 0;
    thread->exit();
    emit exit_return();
}

