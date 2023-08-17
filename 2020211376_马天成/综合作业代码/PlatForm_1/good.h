#ifndef GOOD_H
#define GOOD_H

#include <QString>

enum State{ waiting, sending, received } ;

class Good
{
private:
    /* basic information */
    int      number;        // 序号
    int account_sender;     // 发送方
    int account_receiver;   // 接收方
    QString time_send;      // 发送时间
    QString time_receive;   // 接收时间

    int price;              // 价格
    State   goodState;      // 物品状态，对应枚举类
    QString discription;    // 描述

public:
    Good();
    Good(int sender, int receiver, QString discription);
    void create(int number, int sender, int receiver, QString time_s, QString time_r, int s, double price, QString dis);

    // 获取信息的内联函数
    int& getNumber() {return number;}
    int& getAccountSender() {return account_sender;}
    int& getAccountReceiver() {return account_receiver;}
    QString& getTimeSend() {return time_send;}
    QString& getTimeReceive() {return time_receive;}
    int& getPrice() {return price;}
    State& getGoodState() {return goodState;}
    QString& getDiscription() {return discription;}
};

#endif // GOOD_H
