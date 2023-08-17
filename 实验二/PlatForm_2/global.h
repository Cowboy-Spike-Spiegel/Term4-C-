#ifndef GLOBAL_H
#define GLOBAL_H

#include <windows.h>
#include <ctime>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "basic_Time.h"

extern int handle;
extern FullTime system_Time;
extern LARGE_INTEGER cpuFreq;
extern LARGE_INTEGER starter;
extern LARGE_INTEGER ender;

extern QDir HOME;
extern QSqlDatabase db;

extern int curAccount;
extern QStringList Names;
extern QStringList CourierNames;

#endif // GLOBAL_H
