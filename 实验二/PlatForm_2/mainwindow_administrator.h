#ifndef MAINWINDOW_ADMINISTRATOR_H
#define MAINWINDOW_ADMINISTRATOR_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <vector>
#include "Mythread.h"
#include "global.h"
#include "people.h"

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

    // 管理员身份
    Administrator* admin;

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
    std::vector<Good*> vector_good;
    std::vector<Good*> vector_goodSelect;
    void refreshFindDelivery();

    // 用户查询
    std::vector<User> vector_user;
    std::vector<User> vector_userSelect;
    void refreshFindUser();

    // 快递分配
    void refreshAllocate();
    std::vector<int> delivery_number;   // 记录按钮对应的快递号
    std::vector<QPushButton*> buttons;  // 记录layout的所有按钮
    QVBoxLayout *vLayout;

    // 快递回收机制（输入单号）
    void startRecycle();    // 调用回收机制
    void recycleExpress(int number);

    // 快递员删除机制（输入快递员唯一标识）
    void deleteCarrier(int number);

    // 信息展示
    void refreshShow();

signals:
    void exit_return(); // 返回信号和，方便上一级操作

private slots:
    void on_pushButton_findDelivery_clicked();
    void on_pushButton_findUser_clicked();
    void on_pushButton_allocate_clicked();
    void on_pushButton_refreshShow_clicked();
    void on_pushButton_findRefresh_clicked();
    void on_pushButton_delete_clicked();
};

#endif // MAINWINDOW_ADMINISTRATOR_H
