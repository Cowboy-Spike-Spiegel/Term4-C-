#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>
#include <QTextCodec>
#include "global.h"
#include "people.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 创建用户 创建名单_______________________________
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
            if(curAccount == tmpList.at(0).toInt()) {
                person = new User(curAccount, tmpList.at(1), user, tmpList.at(2).toDouble(),
                                  tmpList.at(3),tmpList.at(4),tmpList.at(5));
            } else ui->comboBox_sendUsers->addItem(tmpList.at(3));  // 顺便生成发送名单，减少遍历数量
            Names.append(tmpList.at(3));    // 生成名单
        }
        // 清理
        strAll.clear();
        strList.clear();
    }
    tempFile.close();

    // thread for time counts and update ____________________________
    thread = new MyThread(this);
    connect(thread, &MyThread::refresh, this, &MainWindow::putTime);
    thread->start();

    // 需要的页面进行初始化，和跳转槽函数 _________________________________________________
    refreshReceive();
    refreshSend();
    refreshFind();
    refreshShow();
    connect(ui->action_receive,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->action_send,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
        connect(ui->action_find,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(2);
    });
    connect(ui->action_recharge,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(3);
    });
    connect(ui->action_show,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(4);
    });
    connect(ui->action_update,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(5);
    });

    setUI();    // 初始化所有页面
    setTime();  // 初始化所有
}

void MainWindow::closeEvent(QCloseEvent *) {
    handle = 0;
    thread->exit(); // 暂停线程
    emit exit_return();
}

// page-receive ******************************************************************************************
void MainWindow::refreshReceive() {
    vector_waitReceive.clear();
    // 查询所有未接收记录
    query.exec("select * from deliverys where receiver = "+QString::number(curAccount)+" and goodstate = 1");
    qDebug() << "select * from deliverys where receiver = "+QString::number(curAccount)+" and goodstate = 1";
    while(query.next()) {
        Good obj;
        obj.create(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toString(),
                   query.value(4).toString(), query.value(5).toInt(), query.value(6).toDouble(), query.value(7).toString());
        vector_waitReceive.push_back(obj);
    }

    // 初始化页面参数（初始化第0面）
    recSize = (int)vector_waitReceive.size();
    recPageIndex = 0;
    if(recSize%SHOWSIZE == 0)   // 生成页面总数
        recPages = recSize/SHOWSIZE;
    else recPages = recSize/SHOWSIZE+1;
    if(recPages == 0) recPages = 1; // 无记录
    qDebug() << "receive" << recSize << recPages;

    // 显示第一页记录
    refreshRecLabels(recPageIndex);
}
void MainWindow::refreshRecLabels(int pageIndex) {
    ui->label_receivePage->setText(QString::number(pageIndex+1)+" / "+QString::number(recPages));
    ui->lineEdit_receivePage->setText("跳转到");

    // 生成当前页面的10个记录
    if(SHOWSIZE*pageIndex < recSize)
        ui->label_receive1->setText(argReceiveStr(SHOWSIZE*pageIndex));
    else    ui->label_receive1->setText("");
    if(SHOWSIZE*pageIndex+1 < recSize)
        ui->label_receive2->setText(argReceiveStr(SHOWSIZE*pageIndex+1));
    else    ui->label_receive2->setText("");
    if(SHOWSIZE*pageIndex+2 < recSize)
        ui->label_receive3->setText(argReceiveStr(SHOWSIZE*pageIndex+2));
    else    ui->label_receive3->setText("");
    if(SHOWSIZE*pageIndex+3 < recSize)
        ui->label_receive4->setText(argReceiveStr(SHOWSIZE*pageIndex+3));
    else    ui->label_receive4->setText("");
    if(SHOWSIZE*pageIndex+4 < recSize)
        ui->label_receive5->setText(argReceiveStr(SHOWSIZE*pageIndex+4));
    else    ui->label_receive5->setText("");
    if(SHOWSIZE*pageIndex+5 < recSize)
        ui->label_receive6->setText(argReceiveStr(SHOWSIZE*pageIndex+5));
    else    ui->label_receive6->setText("");
    if(SHOWSIZE*pageIndex+6 < recSize)
        ui->label_receive7->setText(argReceiveStr(SHOWSIZE*pageIndex+6));
    else    ui->label_receive7->setText("");
    if(SHOWSIZE*pageIndex+7 < recSize)
        ui->label_receive8->setText(argReceiveStr(SHOWSIZE*pageIndex+7));
    else    ui->label_receive8->setText("");
    if(SHOWSIZE*pageIndex+8 < recSize)
        ui->label_receive9->setText(argReceiveStr(SHOWSIZE*pageIndex+8));
    else    ui->label_receive9->setText("");
    if(SHOWSIZE*pageIndex+9 < recSize)
        ui->label_receive10->setText(argReceiveStr(SHOWSIZE*pageIndex+9));
    else    ui->label_receive10->setText("");
}
QString MainWindow::argReceiveStr(int index)
{
    QString sender, time_s, time_r, s, cost;
    sender  = QString("%1 ").arg(Names.at(vector_waitReceive[index].getAccountSender()-1),6,QLatin1Char(' '));
    time_s  = QString("%1 ").arg(vector_waitReceive[index].getTimeSend(),19,QLatin1Char(' '));
    time_r  = QString("%1 ").arg(vector_waitReceive[index].getTimeReceive(),19,QLatin1Char(' '));
    if(vector_waitReceive[index].getGoodState() == waiting) s = "等待揽收";
    else if(vector_waitReceive[index].getGoodState() == sending) s = "等待收货";
    else if(vector_waitReceive[index].getGoodState() == received) s = "收货成功";
    cost    = QString(" %1  ").arg(QString::number(vector_waitReceive[index].getPrice(),'f',2),5,QLatin1Char(' '));

    return sender + time_s + time_r + s + cost + vector_waitReceive[index].getDiscription();
}
void MainWindow::on_pushButton_receiveup_clicked()
{
    if(recPageIndex == 0) {
        QMessageBox mess(QMessageBox::Information,"Warning!","This is first page.");
        mess.exec();
        return;
    }
    recPageIndex--;
    refreshRecLabels(recPageIndex);
}
void MainWindow::on_pushButton_receivedown_clicked()
{
    if(recPageIndex == recPages-1) {
        QMessageBox mess(QMessageBox::Information,"Warning!","This is last page.");
        mess.exec();
        return;
    }
    recPageIndex++;
    refreshRecLabels(recPageIndex);
}
void MainWindow::on_lineEdit_receivePage_returnPressed()
{
    QString input = ui->lineEdit_receivePage->text();
    ui->lineEdit_receivePage->clear();
    for(int i=0; i < input.size(); i++)
        if(input[i] < '0' || input[i] > '9') {
            QMessageBox mess(QMessageBox::Information,"Warning!","Invalid input.");
            mess.exec();
            return;
        }
    int page = input.toInt();
    if(page < 1 || page > recPages) {
        QMessageBox mess(QMessageBox::Information,"Warning!","Page 'input' not exist.");
        mess.exec();
        return;
    }
    recPageIndex = page-1;
    refreshRecLabels(recPageIndex);

}
// 10个对应快递的接收
void MainWindow::on_pushButton_receive1_clicked() {
    if(person->receive(vector_waitReceive[SHOWSIZE*recPageIndex].getNumber(), SHOWSIZE*recPageIndex, recSize)) refreshReceive();
}
void MainWindow::on_pushButton_receive2_clicked() {
    if(person->receive(vector_waitReceive[SHOWSIZE*recPageIndex+1].getNumber(), SHOWSIZE*recPageIndex+1, recSize)) refreshReceive();
}
void MainWindow::on_pushButton_receive3_clicked() {
    if(person->receive(vector_waitReceive[SHOWSIZE*recPageIndex+2].getNumber(), SHOWSIZE*recPageIndex+2, recSize)) refreshReceive();
}
void MainWindow::on_pushButton_receive4_clicked() {
    if(person->receive(vector_waitReceive[SHOWSIZE*recPageIndex+3].getNumber(), SHOWSIZE*recPageIndex+3, recSize)) refreshReceive();
}
void MainWindow::on_pushButton_receive5_clicked() {
    if(person->receive(vector_waitReceive[SHOWSIZE*recPageIndex+4].getNumber(), SHOWSIZE*recPageIndex+4, recSize)) refreshReceive();
}
void MainWindow::on_pushButton_receive6_clicked() {
    if(person->receive(vector_waitReceive[SHOWSIZE*recPageIndex+5].getNumber(), SHOWSIZE*recPageIndex+5, recSize)) refreshReceive();
}
void MainWindow::on_pushButton_receive7_clicked() {
    if(person->receive(vector_waitReceive[SHOWSIZE*recPageIndex+6].getNumber(), SHOWSIZE*recPageIndex+6, recSize)) refreshReceive();
}
void MainWindow::on_pushButton_receive8_clicked() {
    if(person->receive(vector_waitReceive[SHOWSIZE*recPageIndex+7].getNumber(), SHOWSIZE*recPageIndex+7, recSize)) refreshReceive();
}
void MainWindow::on_pushButton_receive9_clicked() {
    if(person->receive(vector_waitReceive[SHOWSIZE*recPageIndex+8].getNumber(), SHOWSIZE*recPageIndex+8, recSize)) refreshReceive();
}
void MainWindow::on_pushButton_receive10_clicked() {
    if(person->receive(vector_waitReceive[SHOWSIZE*recPageIndex+9].getNumber(), SHOWSIZE*recPageIndex+9, recSize)) refreshReceive();
}

// page-send *************************************************************************************************************
void MainWindow::refreshSend() {
    ui->comboBox_sendUsers->setCurrentIndex(-1);
    ui->lineEdit_sendDiscription->clear();
}
void MainWindow::on_pushButton_send_clicked()
{
    // 获取信息
    QString discription = ui->lineEdit_sendDiscription->text();
    int receiver = ui->comboBox_sendUsers->currentIndex()+1;
    if(receiver == 0) {
        QMessageBox mess(QMessageBox::Information,"Warning!","no one selected!");
        mess.exec();
        return;
    }
    // 修正账号number
    if(receiver >= curAccount)  receiver++;

    // 生成Good并发送
    Good obj(curAccount, receiver, discription);
    if(!person->send(obj)) {
        QMessageBox mess(QMessageBox::Information,"Warning!","Balance no enough!");
        mess.exec();
        ui->stackedWidget->setCurrentIndex(3);  // 跳转到充值界面
        return;
    }
    QMessageBox mess(QMessageBox::Information,"Success!","Successfully send!");
    mess.exec();
    ui->comboBox_sendUsers->setCurrentIndex(-1);
    ui->lineEdit_sendDiscription->clear();
}

// page-find ******************************************************************************************
void MainWindow::refreshFind() {
    vector_all.clear();
    // 查询所有相关记录
    query.exec("select * from deliverys where sender = "+QString::number(curAccount)
                                    +" or receiver = "+QString::number(curAccount));
    while(query.next()) {
        Good obj;
        obj.create(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toString(),
                   query.value(4).toString(), query.value(5).toInt(), query.value(6).toDouble(), query.value(7).toString());
        vector_all.push_back(obj);
    }

    // 初始化页面参数，这里选择所有记录（初始化第0面）
    vector_allSelect = vector_all;  // 选择的就是全部
    allSelectSize = (int)vector_allSelect.size();
    allSelectPageIndex = 0;
    if(allSelectSize%SHOWSIZE == 0) // 生成页面总数
        allSelectPages = allSelectSize/SHOWSIZE;
    else allSelectPages = allSelectSize/SHOWSIZE+1;
    if(allSelectPages == 0) allSelectPages = 1; // 无记录
    qDebug() << "all" << allSelectSize << allSelectPages;

    // 显示第一页记录
    refreshAllLabels(allSelectPageIndex);
}
void MainWindow::refreshAllLabels(int pageIndex) {
    // 初始化页面展示
    ui->label_allPage->setText(QString::number(pageIndex+1)+" / "+QString::number(allSelectPages));
    ui->lineEdit_allPage->setText("跳转到");
    ui->comboBox_allSelect->setCurrentIndex(-1);
    ui->comboBox_allSuggest->clear();
    ui->comboBox_allSuggest->hide();
    ui->dateEdit_allSuggest->hide();
    ui->lineEdit_allSuggest->hide();

    // 生成当前页面的10个记录
    if(SHOWSIZE*pageIndex < allSelectSize)
        ui->label_all1->setText(argAllStr(SHOWSIZE*pageIndex));
    else    ui->label_all1->setText("");
    if(SHOWSIZE*pageIndex+1 < allSelectSize)
        ui->label_all2->setText(argAllStr(SHOWSIZE*pageIndex+1));
    else    ui->label_all2->setText("");
    if(SHOWSIZE*pageIndex+2 < allSelectSize)
        ui->label_all3->setText(argAllStr(SHOWSIZE*pageIndex+2));
    else    ui->label_all3->setText("");
    if(SHOWSIZE*pageIndex+3 < allSelectSize)
        ui->label_all4->setText(argAllStr(SHOWSIZE*pageIndex+3));
    else    ui->label_all4->setText("");
    if(SHOWSIZE*pageIndex+4 < allSelectSize)
        ui->label_all5->setText(argAllStr(SHOWSIZE*pageIndex+4));
    else    ui->label_all5->setText("");
    if(SHOWSIZE*pageIndex+5 < allSelectSize)
        ui->label_all6->setText(argAllStr(SHOWSIZE*pageIndex+5));
    else    ui->label_all6->setText("");
    if(SHOWSIZE*pageIndex+6 < allSelectSize)
        ui->label_all7->setText(argAllStr(SHOWSIZE*pageIndex+6));
    else    ui->label_all7->setText("");
    if(SHOWSIZE*pageIndex+7 < allSelectSize)
        ui->label_all8->setText(argAllStr(SHOWSIZE*pageIndex+7));
    else    ui->label_all8->setText("");
    if(SHOWSIZE*pageIndex+8 < allSelectSize)
        ui->label_all9->setText(argAllStr(SHOWSIZE*pageIndex+8));
    else    ui->label_all9->setText("");
    if(SHOWSIZE*pageIndex+9 < allSelectSize)
        ui->label_all10->setText(argAllStr(SHOWSIZE*pageIndex+9));
    else    ui->label_all10->setText("");
}
QString MainWindow::argAllStr(int index) {
    QString number, sender, receiver, time_s, time_r, s, cost;
    number  = QString("%1 ").arg(vector_allSelect[index].getNumber(),4,10,QLatin1Char(' '));
    sender  = QString("%1 ").arg(Names.at(vector_allSelect[index].getAccountSender()-1),6,QLatin1Char(' '));
    receiver= QString("%1 ").arg(Names.at(vector_allSelect[index].getAccountReceiver()-1),6,QLatin1Char(' '));
    time_s  = QString("%1 ").arg(vector_allSelect[index].getTimeSend(),19,QLatin1Char(' '));
    time_r  = QString("%1 ").arg(vector_allSelect[index].getTimeReceive(),19,QLatin1Char(' '));
    if(vector_allSelect[index].getGoodState() == waiting) s = " 等待揽收 ";
    else if(vector_allSelect[index].getGoodState() == sending) s = " 等待收货 ";
    else if(vector_allSelect[index].getGoodState() == received) s = " 收货成功 ";
    cost    = QString(" %1  ").arg(QString::number(vector_allSelect[index].getPrice(),'f',2),5,QLatin1Char(' '));

    return number+sender+receiver+time_s+time_r+s+cost+vector_allSelect[index].getDiscription();
}
// 查询操作相关
void MainWindow::on_pushButton_allRefresh_clicked() {refreshFind();}
void MainWindow::on_pushButton_allSend_clicked()
{
    // 更新选择结果（选择发送方为自己的所有记录）
    vector_allSelect.clear();
    for(unsigned int i=0; i < vector_all.size(); i++)
        if(vector_all[i].getAccountSender() == curAccount)  vector_allSelect.push_back(vector_all[i]);

    // 初始化页面参数，这里选择剩下的记录（初始化第0面）
    allSelectSize = (int)vector_allSelect.size();
    allSelectPageIndex = 0;
    if(allSelectSize%SHOWSIZE == 0) // 生成页面总数
        allSelectPages = allSelectSize/SHOWSIZE;
    else allSelectPages = allSelectSize/SHOWSIZE+1;
    if(allSelectPages == 0) allSelectPages = 1; // 无记录
    qDebug() << "all send" << allSelectSize << allSelectPages;

    // 显示第一页记录
    refreshAllLabels(allSelectPageIndex);
}
void MainWindow::on_pushButton_allReceive_clicked()
{
    // 更新选择结果（选择发送方为自己的所有记录）
    vector_allSelect.clear();
    for(unsigned int i=0; i < vector_all.size(); i++)
        if(vector_all[i].getAccountReceiver() == curAccount)  vector_allSelect.push_back(vector_all[i]);

    // 初始化页面参数，这里选择剩下的记录（初始化第0面）
    allSelectSize = (int)vector_allSelect.size();
    allSelectPageIndex = 0;
    if(allSelectSize%SHOWSIZE == 0) // 生成页面总数
        allSelectPages = allSelectSize/SHOWSIZE;
    else allSelectPages = allSelectSize/SHOWSIZE+1;
    if(allSelectPages == 0) allSelectPages = 1; // 无记录
    qDebug() << "all receive" << allSelectSize << allSelectPages;

    // 显示第一页记录
    refreshAllLabels(allSelectPageIndex);
}
void MainWindow::on_pushButton_allup_clicked()
{
    if(allSelectPageIndex == 0) {
        QMessageBox mess(QMessageBox::Information,"Warning!","This is first page.");
        mess.exec();
        return;
    }
    allSelectPageIndex--;
    refreshAllLabels(allSelectPageIndex);
}
void MainWindow::on_pushButton_alldown_clicked()
{
    if(allSelectPageIndex == allSelectPages-1) {
        QMessageBox mess(QMessageBox::Information,"Warning!","This is last page.");
        mess.exec();
        return;
    }
    allSelectPageIndex++;
    refreshAllLabels(allSelectPageIndex);
}
void MainWindow::on_lineEdit_allPage_returnPressed()
{
    QString input = ui->lineEdit_allPage->text();
    ui->lineEdit_allPage->clear();
    for(int i=0; i < input.size(); i++)
        if(input[i] < '0' || input[i] > '9') {
            QMessageBox mess(QMessageBox::Information,"Warning!","Invalid input.");
            mess.exec();
            return;
        }
    int page = input.toInt();
    if(page < 1 || page > allSelectPages) {
        QMessageBox mess(QMessageBox::Information,"Warning!","Page 'input' not exist.");
        mess.exec();
        return;
    }
    allSelectPageIndex = page-1;
    refreshAllLabels(allSelectPageIndex);
}
void MainWindow::on_comboBox_allSelect_activated(int index)
{
    // 列出发送方
    if(index == 0) {
        ui->comboBox_allSuggest->clear();
        ui->comboBox_allSuggest->show();
        ui->dateEdit_allSuggest->hide();
        ui->lineEdit_allSuggest->hide();
        // 查询名单是否出现
        int* cnt = new int[Names.size()];
        for(int i=0; i < Names.size(); i++) cnt[i]=0;
        for(unsigned int i=0; i < vector_all.size(); i++)
            cnt[vector_all[i].getAccountSender()-1]++;
        // 列出出现名单
        for(int i=0; i < Names.size(); i++)
            if(cnt[i] != 0) ui->comboBox_allSuggest->addItem(Names[i]);
        // 销毁并置0
        delete[] cnt;
        cnt = nullptr;
        // 弄出不选中
        ui->comboBox_allSuggest->setCurrentIndex(-1);
    }
    // 列出接收方
    else if(index == 1) {
        ui->comboBox_allSuggest->clear();
        ui->comboBox_allSuggest->show();
        ui->dateEdit_allSuggest->hide();
        ui->lineEdit_allSuggest->hide();
        // 查询名单是否出现
        int* cnt = new int[Names.size()];
        for(int i=0; i < Names.size(); i++) cnt[i]=0;
        for(unsigned int i=0; i < vector_all.size(); i++)
            cnt[vector_all[i].getAccountReceiver()-1]++;
        // 列出出现名单
        for(int i=0; i < Names.size(); i++)
            if(cnt[i] != 0) ui->comboBox_allSuggest->addItem(Names[i]);
        // 销毁并置0
        delete[] cnt;
        cnt = nullptr;
        // 弄出不选中
        ui->comboBox_allSuggest->setCurrentIndex(-1);
    }
    // 给出时间选择板
    else if(index == 2) {
        ui->comboBox_allSuggest->hide();
        ui->dateEdit_allSuggest->show();
        ui->lineEdit_allSuggest->hide();
    }
    // 给出快递号输入框
    else if(index == 3) {
        ui->comboBox_allSuggest->hide();
        ui->dateEdit_allSuggest->hide();
        ui->lineEdit_allSuggest->show();
    }
}
void MainWindow::on_pushButton_find_clicked()
{
    // 重新生成容器
    vector_allSelect.clear();
    // 对于选择的发送人进行查找筛选
    if(ui->comboBox_allSelect->currentIndex() == 0) {
        QString tmpName = ui->comboBox_allSuggest->currentText();
        for(unsigned int i=0; i < vector_all.size(); i++)
            if(tmpName == Names.at(vector_all[i].getAccountSender()-1)) vector_allSelect.push_back(vector_all[i]);
    }
    else if(ui->comboBox_allSelect->currentIndex() == 1) {
        QString tmpName = ui->comboBox_allSuggest->currentText();
        for(unsigned int i=0; i < vector_all.size(); i++)
            if(tmpName == Names.at(vector_all[i].getAccountReceiver()-1)) vector_allSelect.push_back(vector_all[i]);
    }
    else if(ui->comboBox_allSelect->currentIndex() == 2) {
        QDate date=ui->dateEdit_allSuggest->date();
        QString tmpTime = QString::number(date.year())+"-"+QString::number(date.month())+"-"+QString::number(date.day());
        for(unsigned int i=0; i < vector_all.size(); i++)
            if(vector_all[i].getTimeSend().contains(tmpTime) || vector_all[i].getTimeReceive().contains(tmpTime))
                vector_allSelect.push_back(vector_all[i]);
    }
    else if(ui->comboBox_allSelect->currentIndex() == 3) {
        QString tmpStr = ui->lineEdit_allSuggest->text();
        for(unsigned int i=0; i < vector_all.size(); i++)
            if(QString::number(vector_all[i].getNumber()).contains(tmpStr)) vector_allSelect.push_back(vector_all[i]);
    }
    // 对于筛选记录进行展示
    // 初始化页面参数，这里选择剩下的记录（初始化第0面）
    allSelectSize = (int)vector_allSelect.size();
    allSelectPageIndex = 0;
    if(allSelectSize%SHOWSIZE == 0) // 生成页面总数
        allSelectPages = allSelectSize/SHOWSIZE;
    else allSelectPages = allSelectSize/SHOWSIZE+1;
    if(allSelectPages == 0) allSelectPages = 1; // 无记录
    qDebug() << "all receive" << allSelectSize << allSelectPages;

    // 显示第一页记录
    refreshAllLabels(allSelectPageIndex);
}
// page-recharge **********************************************************************************
void MainWindow::on_pushButton_recharge_clicked()
{
    // 检测输入合法性
    QString input = ui->lineEdit_recharge->text();
    QByteArray bytes = input.toUtf8();
    int flag = 0;   // 标记是否出现过'.'
    int count = 0;  // 标记小数点后的位数
    for(int i=0; i < bytes.length(); i++) {
        if(flag) count++;
        if(bytes[i] == '.')
            flag = 1;
        else if(bytes[i] < '0' || bytes[i] > '9') {
            QMessageBox mess(QMessageBox::Information,"Warning!","Invalid input! Just numbers or '.'");
            mess.exec();
            ui->lineEdit_recharge->clear();
            return;
        }
        if(count > 2) {
            QMessageBox mess(QMessageBox::Information,"Warning!","Invalid input! Just two after '.'");
            mess.exec();
            ui->lineEdit_recharge->clear();
            return;
        }
    }

    double money = input.toDouble();    // 转换汇率
    if(ui->comboBox_recharge->currentIndex() == 1)
        money = money*6.69;
    else if(ui->comboBox_recharge->currentIndex() == 2)
        money = money*7.07;
    else if(ui->comboBox_recharge->currentIndex() == 3)
        money = money*8.36;
    else if(ui->comboBox_recharge->currentIndex() == 4)
        money = money*0.052;
    else if(ui->comboBox_recharge->currentIndex() == 5)
        money = money*13192.07;
    person->refreshBalance(money);  // 加钱

    // 反馈
    QMessageBox mess(QMessageBox::Information,"Success!","Your balance added "+QString::number(money)+"￥.");
    mess.exec();
    ui->lineEdit_recharge->clear();

    // 刷新展示并跳转到信息页面
    refreshShow();
    ui->stackedWidget->setCurrentIndex(4);
}
// page-show ***********************************************************************************
void MainWindow::refreshShow() {
    ui->label_showAccount->setText("  Account: "+QString::number(curAccount));
    ui->label_showName->setText("  Name: "+person->getName());
    ui->label_showTel->setText("  Tel: "+person->getTel());
    ui->label_showAddress->setText("  Address: "+person->getAddress());
    ui->label_showBalance->setText("  Balance: "+QString::number(person->getBalance())+" ￥");
}
// page-update **********************************************************************************
void MainWindow::on_pushButton_update_clicked()
{
    // 输入保存并刷新
    QString name = ui->lineEdit_updateName->text();
    QString tel = ui->lineEdit_updateTel->text();
    QString address = ui->lineEdit_updateAddress->text();
    QString password = ui->lineEdit_updatePassword->text();
    if(name == "输入名称") name = "";
    if(tel == "输入电话") tel = "";
    if(address == "输入地址") address = "";
    if(password == "输入密码") password = "";

    ui->lineEdit_updateName->setText("输入名称");
    ui->lineEdit_updateTel->setText("输入电话");
    ui->lineEdit_updateAddress->setText("输入地址");
    ui->lineEdit_updatePassword->setText("输入密码");

    // 检验合法性
    if(name.contains(" ") || password.contains(" ") || tel.contains(" ") || address.contains(" ")) {
        QMessageBox mess(QMessageBox::Information,"Warning!","No space you input.");
        mess.exec();
        return;
    } else if(!tel.isEmpty() && tel.length() != 11) {
        QMessageBox mess(QMessageBox::Information,"Warning!","Tel.len should be 11.");
        mess.exec();
        return;
    }

    // 需要膝修改密码，先认证
    if(!password.isEmpty()) {
        bool ok;    // 获取用户确定的输入
        QString text = QInputDialog::getText(this, tr("密码修改"),tr("请输入原始密码"), QLineEdit::Password,0, &ok);
        if (!ok || text != person->getPassword()) {
            QMessageBox mess(QMessageBox::Information,"Error!","Authentic fail");
            mess.exec();
            return;
        }
    }

    // 更新
    person->update(name, password, tel, address);
    refreshShow();
    // 跳转到show页面
    ui->stackedWidget->setCurrentIndex(4);
    QMessageBox mess(QMessageBox::Information,"Success!","Update successfully!");
    mess.exec();
}






// 核心功能无关________________________________________________________________________________________________
void MainWindow::setTime() {
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

void MainWindow::putTime() {
    line_year->setText(QString::number(system_Time.get_BigTime().get()[0])+"年");
    line_month->setText(QString::number(system_Time.get_BigTime().get()[1])+"月");
    line_day->setText(QString::number(system_Time.get_BigTime().get()[2])+"日");
    line_hour->setText(QString::number(system_Time.get_SmallTime().get()[0])+"时");
    line_minute->setText(QString::number(system_Time.get_SmallTime().get()[1])+"分");
    line_second->setText(QString::number(system_Time.get_SmallTime().get()[2])+"秒");
}

// __________________________________________________________________________________________________________
void MainWindow::setUI() {
    this->setWindowTitle("User Page");
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

    // page-receive
    ui->label_recTitle->setFont(QFont("Consolas",12,75)) ;
    ui->label_recTitle->setStyleSheet("background: rgba(255,255,255,0%); color: white") ;
    ui->label_recTitle->setText("发送方       发送时间           接收时间            状态    费用    描述");

    ui->label_receive1->setFont(QFont("Consolas",12,75)) ;
    ui->label_receive1->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_receive2->setFont(QFont("Consolas",12,75)) ;
    ui->label_receive2->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_receive3->setFont(QFont("Consolas",12,75)) ;
    ui->label_receive3->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_receive4->setFont(QFont("Consolas",12,75)) ;
    ui->label_receive4->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_receive5->setFont(QFont("Consolas",12,75)) ;
    ui->label_receive5->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_receive6->setFont(QFont("Consolas",12,75)) ;
    ui->label_receive6->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_receive7->setFont(QFont("Consolas",12,75)) ;
    ui->label_receive7->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_receive8->setFont(QFont("Consolas",12,75)) ;
    ui->label_receive8->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_receive9->setFont(QFont("Consolas",12,75)) ;
    ui->label_receive9->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_receive10->setFont(QFont("Consolas",12,75)) ;

    ui->label_receive10->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->pushButton_receive1->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->pushButton_receive1->setStyleSheet("background: rgba(180,235,255,75%)") ;
    ui->pushButton_receive2->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->pushButton_receive2->setStyleSheet("background: rgba(180,235,255,75%)") ;
    ui->pushButton_receive3->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->pushButton_receive3->setStyleSheet("background: rgba(180,235,255,75%)") ;
    ui->pushButton_receive4->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->pushButton_receive4->setStyleSheet("background: rgba(180,235,255,75%)") ;
    ui->pushButton_receive5->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->pushButton_receive5->setStyleSheet("background: rgba(180,235,255,75%)") ;
    ui->pushButton_receive6->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->pushButton_receive6->setStyleSheet("background: rgba(180,235,255,75%)") ;
    ui->pushButton_receive7->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->pushButton_receive7->setStyleSheet("background: rgba(180,235,255,75%)") ;
    ui->pushButton_receive8->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->pushButton_receive8->setStyleSheet("background: rgba(180,235,255,75%)") ;
    ui->pushButton_receive9->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->pushButton_receive9->setStyleSheet("background: rgba(180,235,255,75%)") ;
    ui->pushButton_receive10->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->pushButton_receive10->setStyleSheet("background: rgba(180,235,255,75%)") ;

    ui->pushButton_receiveup->setFont(QFont("Microsoft YaHei",8,75)) ;
    ui->pushButton_receiveup->setStyleSheet("background: rgba(180,235,255,50%)") ;
    ui->pushButton_receivedown->setFont(QFont("Microsoft YaHei",8,75)) ;
    ui->pushButton_receivedown->setStyleSheet("background: rgba(180, 235,255,50%)") ;
    ui->lineEdit_receivePage->setFont(QFont("Consolas",8)) ;
    ui->lineEdit_receivePage->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_receivePage->setFont(QFont("Consolas",12,75)) ;
    ui->label_receivePage->setStyleSheet("background: rgba(255,255,255,50%)") ;

    // page-send
    ui->comboBox_sendUsers->setFont(QFont("Microsoft YaHei",20,75)) ;
    ui->comboBox_sendUsers->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->lineEdit_sendDiscription->setFont(QFont("Microsoft YaHei",20,75)) ;
    ui->lineEdit_sendDiscription->setStyleSheet("background: rgba(255,255,255,50%);color: white") ;
    ui->pushButton_send->setFont(QFont("Microsoft YaHei",20,75)) ;
    ui->pushButton_send->setStyleSheet("background: rgba(255,255,255,50%)") ;

    // page-find
    ui->label_allTitle->setFont(QFont("Consolas",12,75)) ;
    ui->label_allTitle->setStyleSheet("background: rgba(255,255,255,0%); color: white") ;
    ui->label_allTitle->setText("单号  发送方   接收方    发送时间         接收时间       状态   费用   描述");
    ui->label_all1->setFont(QFont("Consolas",10,75)) ;
    ui->label_all1->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_all2->setFont(QFont("Consolas",10,75)) ;
    ui->label_all2->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_all3->setFont(QFont("Consolas",10,75)) ;
    ui->label_all3->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_all4->setFont(QFont("Consolas",10,75)) ;
    ui->label_all4->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_all5->setFont(QFont("Consolas",10,75)) ;
    ui->label_all5->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_all6->setFont(QFont("Consolas",10,75)) ;
    ui->label_all6->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_all7->setFont(QFont("Consolas",10,75)) ;
    ui->label_all7->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_all8->setFont(QFont("Consolas",10,75)) ;
    ui->label_all8->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_all9->setFont(QFont("Consolas",10,75)) ;
    ui->label_all9->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_all10->setFont(QFont("Consolas",10,75)) ;
    ui->label_all10->setStyleSheet("background: rgba(255,255,255,50%)") ;

    ui->pushButton_allup->setFont(QFont("Microsoft YaHei",8,75)) ;
    ui->pushButton_allup->setStyleSheet("background: rgba(180,235,255,50%)") ;
    ui->pushButton_alldown->setFont(QFont("Microsoft YaHei",8,75)) ;
    ui->pushButton_alldown->setStyleSheet("background: rgba(180, 235,255,50%)") ;
    ui->lineEdit_allPage->setFont(QFont("Consolas",8)) ;
    ui->lineEdit_allPage->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_allPage->setFont(QFont("Consolas",12,75)) ;
    ui->label_allPage->setStyleSheet("background: rgba(255,255,255,50%)") ;

    ui->pushButton_allSend->setFont(QFont("Microsoft YaHei",10,75)) ;
    ui->pushButton_allSend->setStyleSheet("background: rgba(180, 235,255,50%)") ;
    ui->pushButton_allReceive->setFont(QFont("Microsoft YaHei",10,75)) ;
    ui->pushButton_allReceive->setStyleSheet("background: rgba(180, 235,255,50%)") ;

    ui->comboBox_allSelect->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->comboBox_allSelect->setStyleSheet("background: rgba(255,255,255,75%)") ;
    ui->comboBox_allSelect->setCurrentIndex(-1);
    ui->comboBox_allSuggest->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->comboBox_allSuggest->setStyleSheet("background: rgba(255,255,255,75%)") ;
    ui->comboBox_allSuggest->hide();
    ui->dateEdit_allSuggest->setFont(QFont("Consolas",12,75)) ;
    ui->dateEdit_allSuggest->setStyleSheet("background: rgba(255,255,255,75%)") ;
    ui->dateEdit_allSuggest->hide();
    ui->lineEdit_allSuggest->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->lineEdit_allSuggest->setStyleSheet("background: rgba(255,255,255,75%)") ;
    ui->lineEdit_allSuggest->hide();
    ui->pushButton_find->setFont(QFont("Microsoft YaHei",15,75)) ;
    ui->pushButton_find->setStyleSheet("background: rgba(180,235,255,50%)") ;

    // page-recharge
    ui->lineEdit_recharge->setFont(QFont("Microsoft YaHei",20,75)) ;
    ui->lineEdit_recharge->setStyleSheet("background: rgba(255,255,255,50%);color: white") ;
    ui->comboBox_recharge->setFont(QFont("Microsoft YaHei",20,75)) ;
    ui->comboBox_recharge->setStyleSheet("background: rgba(255,255,255,50%);color: white") ;
    ui->comboBox_recharge->addItem("CNY ¥");
    ui->comboBox_recharge->addItem("$");    // 6.69
    ui->comboBox_recharge->addItem("₣");    // 7.07
    ui->comboBox_recharge->addItem("£");    // 8.36
    ui->comboBox_recharge->addItem("JPY ¥");// 0.052
    ui->comboBox_recharge->addItem("ETH");  // 13192.07
    ui->pushButton_recharge->setFont(QFont("Microsoft YaHei",20,75)) ;
    ui->pushButton_recharge->setStyleSheet("background: rgba(255,255,255,50%)") ;

    // page-show
    ui->label_showAccount->setFont(QFont("Consolas",18,75)) ;
    ui->label_showAccount->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_showName->setFont(QFont("Consolas",18,75)) ;
    ui->label_showName->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_showTel->setFont(QFont("Consolas",18,75)) ;
    ui->label_showTel->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_showAddress->setFont(QFont("Consolas",18,75)) ;
    ui->label_showAddress->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->label_showBalance->setFont(QFont("Consolas",18,75)) ;
    ui->label_showBalance->setStyleSheet("background: rgba(255,255,255,50%)") ;

    // page-update
    ui->lineEdit_updateName->setFont(QFont("Consolas",18,75)) ;
    ui->lineEdit_updateName->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->lineEdit_updateTel->setFont(QFont("Consolas",18,75)) ;
    ui->lineEdit_updateTel->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->lineEdit_updateAddress->setFont(QFont("Consolas",18,75)) ;
    ui->lineEdit_updateAddress->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->lineEdit_updatePassword->setFont(QFont("Consolas",18,75)) ;
    ui->lineEdit_updatePassword->setStyleSheet("background: rgba(255,255,255,50%)") ;
    ui->pushButton_update->setFont(QFont("Microsoft YaHei",18,75)) ;
    ui->pushButton_update->setStyleSheet("background: rgba(180,235,255,50%)") ;
    ui->lineEdit_updateName->setText("输入名称");
    ui->lineEdit_updateTel->setText("输入电话");
    ui->lineEdit_updateAddress->setText("输入地址");
    ui->lineEdit_updatePassword->setText("输入密码");
}

MainWindow::~MainWindow()
{
    // 账号归0，清空登陆状态
    curAccount = 0;

    // 删除状态栏时间控件
    delete line_year;
    delete line_month;
    delete line_day;
    delete line_hour;
    delete line_minute;
    delete line_second;
    // 保存时间
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
    // 删除时间线程（closeEvent触发时已经停止，可安全关闭）
    delete thread;
    thread = NULL;

    delete ui;
    Names.clear();
}

