#ifndef GLOBAL_H
#define GLOBAL_H

#include <windows.h>
#include <ctime>
#include <QDir>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "basic_Time.h"

// 系统时间相关
extern int handle;
extern FullTime system_Time;
extern LARGE_INTEGER cpuFreq;
extern LARGE_INTEGER starter;
extern LARGE_INTEGER ender;

// 数据相关
extern QDir HOME;
extern QSqlDatabase db;

// socket相关
extern QTcpSocket* qsocket;
extern QByteArray array;

// 所需信息相关
extern int curAccount;
extern QStringList Names;
extern QStringList CourierNames;

#endif // GLOBAL_H
