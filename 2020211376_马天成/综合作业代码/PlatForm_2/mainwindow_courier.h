#ifndef MAINWINDOW_COURIER_H
#define MAINWINDOW_COURIER_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <vector>
#include "Mythread.h"
#include "global.h"
#include "people.h"

namespace Ui {
class MainWindow_Courier;
}

class MainWindow_Courier : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_Courier(QWidget *parent = nullptr);
    ~MainWindow_Courier();

private:
    Ui::MainWindow_Courier *ui;
    void setUI();
    void closeEvent(QCloseEvent *);

    Courier* person;    // 快递员

    // 配送
    void refreshDelivery();
    std::vector<int> delivery_number;   // 记录按钮对应的快递号
    std::vector<double> money;  // 记录费用
    std::vector<QPushButton*> buttons;  // 记录layout的所有按钮
    QVBoxLayout *vLayout;

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

signals:
    void exit_return();
private slots:
    void on_pushButton_reject_clicked();
    void on_pushButton_delivery_clicked();
};

#endif // MAINWINDOW_COURIER_H
