#include "Mythread.h"
#include <windows.h>
#include <QDebug>
#include "global.h"

MyThread::MyThread(QObject *parent)
    : QThread(parent)
{}

void MyThread::run() {
    handle = 1;
    QueryPerformanceFrequency(&cpuFreq);
    QueryPerformanceCounter(&starter);
    while(handle) {
        QueryPerformanceCounter(&ender);
        if( (ender.QuadPart-starter.QuadPart) >= 277777.78 ) {
            system_Time.second_Pass();
            emit refresh();
            QueryPerformanceCounter(&starter);
        }
    }
}
