#include "people.h"
#include "global.h"
#include <QDebug>
#include <QTextCodec>

// _________________________________________________________________________________________________________________________
People::People(int account, QString password, Permission identity)
{
    this->account   = account;
    this->password  = password;
    this->identity  = identity;
}
People::~People() {}

// _________________________________________________________________________________________________________________________
User::User(int account, QString password, Permission identity, double  balance, QString name, QString tel, QString address)
    : People(account, password, identity) {
    this->balance   = balance;
    this->name      = name;
    this->tel       = tel;
    this->address   = address;
}
bool User::send(Good* obj) {
    // 余额不足，直接返回
    if(obj->getPrice()*obj->getWeight() > this->balance)
        return false;

    QString cmd = "insert into delivery_improve(number, sender, receiver, time_send, time_receive, weight, cost, goodstate, discription, courier) values";
    cmd+="("+QString::number(+obj->getNumber())+","
            +QString::number(obj->getAccountSender())+","
            +QString::number(obj->getAccountReceiver())+","
            +"'"+obj->getTimeSend()+"',"
            +"'"+obj->getTimeReceive()+"',"
            +QString::number(obj->getWeight())+","
            +QString::number(obj->getPrice()*obj->getWeight(),'f',6)+","
            +QString::number(waiting)+","
            +"'"+obj->getDiscription()+"',0)";
    qDebug() << cmd;
    QSqlQuery query;
    query.exec(cmd);

    // 刷新账户余额
    this->refreshBalance(-obj->getPrice()*obj->getWeight());

    // 传给服务端进行管理员账户的余额刷新（默认给第一个管理员）
    QString str = "admin_balanceChange " + QString::number(obj->getPrice()*obj->getWeight());
    qsocket->write(str.toUtf8());
    qsocket->waitForReadyRead();
    array = qsocket->readAll();
    str = QString(array);
    qDebug() << str;

    return true;
}
bool User::receive(int number, int index, int size) const {
    if(index < size) {
        QString str;
        QSqlQuery query;
        str = "update delivery_improve set goodstate = 2, ";
        str +="time_receive = '"
            + QString::number(system_Time.get_BigTime().get()[0]) + "-"
            + QString::number(system_Time.get_BigTime().get()[1]) + "-"
            + QString::number(system_Time.get_BigTime().get()[2]) + "-"
            + QString::number(system_Time.get_SmallTime().get()[0]) + "-"
            + QString::number(system_Time.get_SmallTime().get()[1]) + "-"
            + QString::number(system_Time.get_SmallTime().get()[2]) + "'";
        str +=" where number = "+QString::number(number);
        query.exec(str);
        return true;
    }
    return false;
}

// 更新余额
void User::refreshBalance(double money) {
    // 扣除
    this->balance = this->balance + money;

    // 传给服务端进行本人充值
    QString str = "user_balanceChange " + QString::number(account) + " " +QString::number(money);
    qsocket->write(str.toUtf8());
    qsocket->waitForReadyRead();
    array = qsocket->readAll();
    str = QString(array);
    qDebug() << str;
}

// 更新信息，输入可为空
void User::update(QString name, QString password, QString tel, QString address) {

    // 传给服务端进行信息修改
    QString str = "user_update " + QString::number(account) + " " +name+" "+password+" "+tel+" "+address;
    qsocket->write(str.toUtf8());
    qsocket->waitForReadyRead();
    array = qsocket->readAll();
    str = QString(array);
    qDebug() << str;

    // 最后更新当前数值
    if(name != "%")
        this->name = name;
    if(password != "%")
        this->password = password;
    if(tel != "%")
        this->tel = tel;
    if(address != "%")
        this->address = address;
}

// _________________________________________________________________________________________________________________________
Courier::Courier(int account, QString password, Permission identity, double  balance, QString name, QString tel, QString address)
    : People(account, password, identity) {
    this->balance   = balance;
    this->name      = name;
    this->tel       = tel;
    this->address   = address;
}
void Courier::distribute(int number, double money) {

    // 在管理员账户中取出
    QString str = "admin_balanceChange " + QString::number(-money);
    qsocket->write(str.toUtf8());
    qsocket->waitForReadyRead();
    array = qsocket->readAll();
    str = QString(array);
    qDebug() << str;

    // 给自己账户加上
    str = "courier_balanceChange " + QString::number(account) + " " + QString::number(money);
    qsocket->write(str.toUtf8());
    qsocket->waitForReadyRead();
    array = qsocket->readAll();
    str = QString(array);
    qDebug() << str;

    // 更新
    QSqlQuery query;
    query.exec("update delivery_improve set goodstate = '2', courier = "+QString::number(account)+
               " where number = "+QString::number(number));
    qDebug() << "update delivery_improve set goodstate = '2', courier = "+QString::number(account)+
                " where number = "+QString::number(number);

    // 账户信息也更新
    this->balance = this->balance+money;
}
void Courier::reject(int number) const{
    QSqlQuery query;
    query.exec("update delivery_improve set goodstate = '0', courier = 0 where number = "+QString::number(number));
    qDebug() << "update delivery_improve set goodstate = '0', courier = 0 where number = "+QString::number(number);
}


// _________________________________________________________________________________________________________________________
Administrator::Administrator(int account, QString password, Permission identity, double  balance, QString name, QString tel)
    : People(account, password, identity) {
    this->balance   = balance;
    this->name      = name;
    this->tel       = tel;
}
void Administrator::deleteCourier(int number) {
    QString str = "admin_deleteCourier " + QString::number(number);
    qsocket->write(str.toUtf8());
    qsocket->waitForReadyRead();
    array = qsocket->readAll();
    str = QString(array);
    qDebug() << str;
}
