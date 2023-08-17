#include "good.h"
#include "global.h"

Good::Good() {}

void Good::create(int sender, int receiver, int weight, QString discription)
{
    // 生成快递号
    QSqlQuery query;
    query.exec("select * from delivery_improve");
    this->number = query.size()+1;

    // 录入信息
    this->account_sender = sender;
    this->account_receiver = receiver;
    this->weight = weight;
    this->discription = discription;
    this->goodState = waiting;      // 默认等待揽收

    // 设定发送时间
    this->time_send = QString::number(system_Time.get_BigTime().get()[0]) + "-"
                    + QString::number(system_Time.get_BigTime().get()[1]) + "-"
                    + QString::number(system_Time.get_BigTime().get()[2]) + "-"
                    + QString::number(system_Time.get_SmallTime().get()[0]) + "-"
                    + QString::number(system_Time.get_SmallTime().get()[1]) + "-"
                    + QString::number(system_Time.get_SmallTime().get()[2]);
    this->time_receive = "";
}

// 快速构造
void Good::create(int number, int sender, int receiver, QString time_s, QString time_r, int weight, int s, QString dis, int c)
{
    this->number = number;
    this->account_sender = sender;
    this->account_receiver = receiver;
    this->time_send = time_s;
    this->time_receive = time_r;
    this->weight = weight;
    if(s == 0)
        this->goodState = waiting;
    else if(s == 1)
        this->goodState = sending;
    else if(s == 2)
        this->goodState = received;
    this->discription = dis;
    this->courier = c;
}
