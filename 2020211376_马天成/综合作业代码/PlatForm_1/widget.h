#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "signup.h"
#include "mainwindow.h"
#include "mainwindow_administrator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_signin_clicked();
    void on_pushButton_signup_clicked();

    void on_lineEdit_password_returnPressed();

private:
    Ui::Widget *ui;
    void setUI();

    void setHOMEPath();
    void linkDatabase();

    SignUp* sign;
    MainWindow* userPage;
    MainWindow_Administrator* administratorPage;
};
#endif // WIDGET_H
