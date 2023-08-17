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

    bool send(Good* obj) ;   // 发送快递（纯虚函数）
    bool receive(int number, int index, int size) const;  // 接收快递
    void refreshBalance(double money);  // 更新账户余额（有正负值）

    // 返回元素
    double getBalance() {return this->balance;}
    QString getName() {return this->name;}
    QString getTel() {return this->tel;}
    QString getAddress() {return this->address;}

    // 修改函数
    void update(QString name, QString password, QString tel, QString address);
};

// _________________________________________________________________
class Courier : public People
{
private:
    /* necessary elements */
    double  balance;    // 余额
    QString name;       // 名称
    QString tel;        // 电话
    QString address;    // 地址

public:
    Courier(int account, QString password, Permission identity, double  balance, QString name, QString tel, QString address);

    void distribute(int number, double money);     // 配送快递
    void reject(int number) const;              // （但是，我）拒绝配送
    double getBalance() {return this->balance;}
    QString getName() {return this->name;}
    QString getTel() {return this->tel;}
};

// _________________________________________________________________
class Administrator : public People
{
private:
    double  balance;    // 余额
    QString name;       // 名称
    QString tel;        // 电话
public:
    Administrator(int account, QString password, Permission identity, double balance, QString name, QString tel);
    void deleteCourier(int number);

    double getBalance() {return this->balance;}
    QString getName() {return this->name;}
    QString getTel() {return this->tel;}
};

#endif // PEOPLE_H
