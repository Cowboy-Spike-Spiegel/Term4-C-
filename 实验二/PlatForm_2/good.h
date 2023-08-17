#ifndef GOOD_H
#define GOOD_H

#include <QString>

enum State{ waiting, sending, received } ;

class Good
{
protected:
    /* basic information */
    int      number;        // 序号
    int account_sender;     // 发送方
    int account_receiver;   // 接收方
    QString time_send;      // 发送时间
    QString time_receive;   // 接收时间
    int weight;             // 快递重量 1-10

    State   goodState;
    QString discription;
    int courier;    // 快递员编号

public:
    Good();
    void create(int sender, int receiver, int weight, QString discription);
    void create(int number, int sender, int receiver, QString time_s, QString time_r, int weight, int s, QString dis, int c);

    // 获取信息的内联函数
    virtual int getPrice() = 0;    // 纯虚函数
    int& getNumber() {return number;}
    int& getAccountSender() {return account_sender;}
    int& getAccountReceiver() {return account_receiver;}
    QString& getTimeSend() {return time_send;}
    QString& getTimeReceive() {return time_receive;}
    int& getWeight() {return weight;}
    State& getGoodState() {return goodState;}
    QString& getDiscription() {return discription;}
    int& getCoutier() {return this->courier;}
};

class Good_Fragile : public Good
{
public:
    int getPrice() {return 8;}
};

class Good_Book : public Good
{
public:
    int getPrice() {return 2;}
};

class Good_Normal : public Good
{
public:
    int getPrice() {return 5;}
};
#endif // GOOD_H
