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

// _________________________________________________________________________________________________________________________
User::User(int account, QString password, Permission identity, double  balance, QString name, QString tel, QString address)
    : People(account, password, identity) {
    this->balance   = balance;
    this->name      = name;
    this->tel       = tel;
    this->address   = address;
}
bool User::send(Good& obj) {
    // 余额不足，直接返回
    if(obj.getPrice() > this->balance)
        return false;

    QString cmd = "insert into deliverys(number, sender, receiver, time_send, time_receive, goodstate, cost, discription) values";
    cmd+="("+QString::number(+obj.getNumber())+","
            +QString::number(obj.getAccountSender())+","
            +QString::number(obj.getAccountReceiver())+","
            +"'"+obj.getTimeSend()+"',"
            +"'"+obj.getTimeReceive()+"',"
            +QString::number(sending)+","
            +QString::number(obj.getPrice(),'f',6)+","
            +"'"+obj.getDiscription()+"')";
    qDebug() << cmd;
    QSqlQuery query;
    query.exec(cmd);

    // 刷新账户余额
    this->refreshBalance(-15);

    // 转给管理员
    QDir tempDir(HOME.absolutePath()+"/data");
    QFile tempFile;     // 打开的文件
    QString strAll;     // 全部信息
    QStringList strList;// 分割信息
    QStringList tmpList;// 暂存分割信息
    // 读出信息
    tempFile.setFileName(tempDir.absolutePath()+"/Administrator");
    if(tempFile.open((QIODevice::ReadOnly|QIODevice::Text))) {
        QTextStream stream(&tempFile);  // 打开流，读出
        stream.setCodec(QTextCodec::codecForName("utf-8")); // 规定utf8
        strAll=stream.readAll();
        strList=strAll.split('\n');
    }
    tempFile.close();
    // 写回信息
    tempFile.setFileName(tempDir.absolutePath()+"/Administrator");
    if(tempFile.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QTextStream stream(&tempFile);  // 打开流，写入
        stream.setCodec(QTextCodec::codecForName("utf-8")); // 规定utf8
        // 写第一行
        tmpList = strList.at(0).split(" ");
        stream << tmpList.at(0)+" "+tmpList.at(1)+" "+QString::number(obj.getPrice()+tmpList.at(2).toDouble(),'f',6)+" "
                  +tmpList.at(3)+" "+tmpList.at(4)+"\n";
        // 写后面的
        for(int i=1; i < strList.count(); i++) {
            stream << strList.at(i);
            if(i != strList.count()-1 ) stream << '\n';
        }
        // 清理
        strAll.clear();
        strList.clear();
    }
    tempFile.close();

    return true;
}
bool User::receive(int number, int index, int size) const {
    if(index < size) {
        QString str;
        QSqlQuery query;
        str = "update deliverys set goodstate = 2, ";
        str +="time_receive = '"
            + QString::number(system_Time.get_BigTime().get()[0]) + "-"
            + QString::number(system_Time.get_BigTime().get()[1]) + "-"
            + QString::number(system_Time.get_BigTime().get()[2]) + "-"
            + QString::number(system_Time.get_SmallTime().get()[0]) + "-"
            + QString::number(system_Time.get_SmallTime().get()[1]) + "-"
            + QString::number(system_Time.get_SmallTime().get()[2]) + "'";
        str +="where number = "+QString::number(number);
        qDebug() << str;
        query.exec(str);
        return true;
    }
    return false;
}

void User::refreshBalance(double money) {
    // 扣除
    this->balance = this->balance + money;
    qDebug() << this->balance;

    // 更新文件
    QDir tempDir(HOME.absolutePath()+"/data");
    QFile tempFile;     // 打开的文件
    QString strAll;     // 全部信息
    QStringList strList;// 分割信息
    QStringList tmpList;// 暂存分割信息
    // 读出信息
    tempFile.setFileName(tempDir.absolutePath()+"/User");
    if(tempFile.open((QIODevice::ReadOnly|QIODevice::Text))) {
        QTextStream stream(&tempFile);  // 打开流，读出
        stream.setCodec(QTextCodec::codecForName("utf-8")); // 规定utf8
        strAll=stream.readAll();
        strList=strAll.split('\n');
    }
    tempFile.close();
    // 写回信息
    tempFile.setFileName(tempDir.absolutePath()+"/User");
    if(tempFile.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QTextStream stream(&tempFile);  // 打开流，写入
        stream.setCodec(QTextCodec::codecForName("utf-8")); // 规定utf8
        for(int i=0; i<strList.count(); i++) {
            // 分割单行
            tmpList = strList.at(i).split(" ");
            if(curAccount == tmpList.at(0).toInt()) {
                stream << tmpList.at(0)+" "+tmpList.at(1)+" "+QString::number(this->balance,'f',6)+" "
                          +tmpList.at(3)+" "+tmpList.at(4)+" "+tmpList.at(5)+"\n";
            } else
                stream << strList.at(i);
            if(i != strList.count()-1 ) stream << '\n';
        }
        // 清理
        strAll.clear();
        strList.clear();
    }
    tempFile.close();
}

// 输入可为空
void User::update(QString name, QString password, QString tel, QString address) {
    // 更新文件
    QDir tempDir(HOME.absolutePath()+"/data");
    QFile tempFile;     // 打开的文件
    QString strAll;     // 全部信息
    QStringList strList;// 分割信息
    QStringList tmpList;// 暂存分割信息

    // 读出信息
    tempFile.setFileName(tempDir.absolutePath()+"/User");
    if(tempFile.open((QIODevice::ReadOnly|QIODevice::Text))) {
        QTextStream stream(&tempFile);  // 打开流，读出
        stream.setCodec(QTextCodec::codecForName("utf-8")); // 规定utf8
        strAll=stream.readAll();
        strList=strAll.split('\n');
    }
    tempFile.close();
    // 写回信息
    tempFile.setFileName(tempDir.absolutePath()+"/User");
    if(tempFile.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QTextStream stream(&tempFile);  // 打开流，写入
        stream.setCodec(QTextCodec::codecForName("utf-8")); // 规定utf8
        for(int i=0; i<strList.count(); i++) {
            // 分割单行
            tmpList = strList.at(i).split(" ");
            // 找到，修改
            if(this->account == tmpList.at(0).toInt()) {
                // 规格化输入，空串忽略
                if(name.isEmpty()) name = tmpList.at(3);
                if(password.isEmpty()) password = tmpList.at(1);
                if(tel.isEmpty()) tel = tmpList.at(4);
                if(address.isEmpty()) address = tmpList.at(5);
                stream << tmpList.at(0)+" "+password+" "+tmpList.at(2)+" "
                          +name+" "+tel+" "+address;
            } else
                stream << strList.at(i); 
            if(i != strList.count()-1 ) stream << '\n';
        }
        // 清理
        strAll.clear();
        strList.clear();
    }
    tempFile.close();

    // 最后更新当前数值
    this->name = name;
    this->password = password;
    this->tel = tel;
    this->address = address;
}

// _________________________________________________________________________________________________________________________
Administrator::Administrator(int account, QString password, Permission identity, double  balance, QString name, QString tel)
    : People(account, password, identity) {
    this->balance   = balance;
    this->name      = name;
    this->tel       = tel;
}
