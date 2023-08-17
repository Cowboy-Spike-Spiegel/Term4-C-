#ifndef PEOPLE_H
#define PEOPLE_H

#include <QString>
#include "good.h"

enum Permission{ user, courier, administrator } ;

// _________________________________________________________________
class People
{
protected:
    /* basic information */
    int         account;
    QString     password;
    Permission  identity;

public:
    People(int account, QString password, Permission identity);

    int getAccount() {return this->account;};
    QString getPassword() {return this->password;};
    Permission getIdentity() {return this->identity;};
};

// _________________________________________________________________
class User : public People
{
private:
    /* necessary elements */
    double  balance;    // 余额
    QString name;       // 名称
    QString tel;        // 电话
    QString address;    // 地址
public:
    User(int account, QString password, Permission identity, double  balance, QString name, QString tel, QString address);

    bool send(Good& obj);
    bool receive(int number, int index, int size) const;
    void refreshBalance(double money);

    double getBalance() {return this->balance;}
    QString getName() {return this->name;}
    QString getTel() {return this->tel;}
    QString getAddress() {return this->address;}

    // 修改函数
    void update(QString name, QString password, QString tel, QString address);
};

// _________________________________________________________________
class Administrator : public People
{
private:
    double  balance;    // 余额
    QString name;       // 名称
    QString tel;        // 电话
public:
    Administrator(int account, QString password, Permission identity, double  balance, QString name, QString tel);

    double getBalance() {return this->balance;}
    QString getName() {return this->name;}
    QString getTel() {return this->tel;}
};

#endif // PEOPLE_H
