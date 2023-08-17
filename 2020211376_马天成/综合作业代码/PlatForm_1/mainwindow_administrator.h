#ifndef MAINWINDOW_ADMINISTRATOR_H
#define MAINWINDOW_ADMINISTRATOR_H

#include <QMainWindow>
#include <QLabel>
#include <QSqlQuery>
#include <vector>
#include "Mythread.h"
#include "people.h"
#include "good.h"

namespace Ui {
class MainWindow_Administrator;
}

class MainWindow_Administrator : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_Administrator(QWidget *parent = nullptr);
    ~MainWindow_Administrator();

private:
    Ui::MainWindow_Administrator *ui;
    void setUI();
    void closeEvent(QCloseEvent *);

    // 时间模拟和状态栏展示
    MyThread* thread;
    void setTime();
    void putTime();
    QLabel* line_year;
    QLabel* line_month;
    QLabel* line_day;
    QLabel* line_hour;
    QLabel* line_minute;
    QLabel* line_second;

    QSqlQuery query;    // 查询

    // 快递查询
    std::vector<Good> vector_good;
    std::vector<Good> vector_goodSelect;
    void refreshFindDelivery();

    // 用户查询
    std::vector<User> vector_user;
    std::vector<User> vector_userSelect;
    void refreshFindUser();

    // 信息展示
    void refreshShow();

signals:
    void exit_return(); // 返回信号和，方便上一级操作
private slots:
    void on_pushButton_findDelivery_clicked();
    void on_pushButton_findUser_clicked();
};

#endif // MAINWINDOW_ADMINISTRATOR_H
