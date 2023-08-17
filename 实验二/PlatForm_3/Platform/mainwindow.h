#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <vector>
#include "Mythread.h"
#include "global.h"
#include "people.h"

#define SHOWSIZE 10 // 单个窗口显示记录数

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void setUI();
    void closeEvent(QCloseEvent *);

    User* person;   // 用户

    // 线程模拟时间并在状态栏输出
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

    // receive-page
    void refreshReceive();
    void refreshRecLabels(int pageIndex);   // 刷新第几页记录
    QString argReceiveStr(int index);       // 格式化生成第几条记录
    std::vector<Good*> vector_waitReceive;  // 装未接收的Good(有虚函数，用指针)
    int recSize;        // 总记录数
    int recPageIndex;   // 记录当前查询页面下标（0开始）
    int recPages;       // 记录总页面数

    // send-page
    void refreshSend();

    // find-page
    std::vector<Good*> vector_all;  // 全部相关结果集
    void refreshFind();
    void refreshAllLabels(int pageIndex);
    QString argAllStr(int index);
    std::vector<Good*> vector_allSelect;    // 筛选后的结果集
    int allSelectSize;
    int allSelectPageIndex;
    int allSelectPages;

    // 初始化个人信息展示页面
    void refreshShow();

private slots:
    // receive-page
    void on_pushButton_receiveup_clicked();
    void on_pushButton_receivedown_clicked();
    void on_lineEdit_receivePage_returnPressed();
    void on_pushButton_receive1_clicked();
    void on_pushButton_receive2_clicked();
    void on_pushButton_receive3_clicked();
    void on_pushButton_receive4_clicked();
    void on_pushButton_receive5_clicked();
    void on_pushButton_receive6_clicked();
    void on_pushButton_receive7_clicked();
    void on_pushButton_receive8_clicked();
    void on_pushButton_receive9_clicked();
    void on_pushButton_receive10_clicked();
    // send-page
    void on_pushButton_send_clicked();
    // find-page
    void on_pushButton_allRefresh_clicked();
    void on_pushButton_allSend_clicked();
    void on_pushButton_allReceive_clicked();
    void on_pushButton_allup_clicked();
    void on_pushButton_alldown_clicked();
    void on_lineEdit_allPage_returnPressed();
    void on_comboBox_allSelect_activated(int index);
    void on_pushButton_find_clicked();
    // recharge-page
    void on_pushButton_recharge_clicked();
    // show-page
    void on_pushButton_clicked();
    // update-page
    void on_pushButton_update_clicked();

signals:
    void exit_return();
};

#endif // MAINWINDOW_H
