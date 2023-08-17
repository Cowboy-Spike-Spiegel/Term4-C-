#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>

namespace Ui {
class SignUp;
}

class SignUp : public QWidget
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

private:
    Ui::SignUp *ui;
    void setUI();

    // 重写关闭函数
    void closeEvent(QCloseEvent *);

signals:
    void exit_return();
private slots:
    void on_pushButton_clicked();
};

#endif // SIGNUP_H
