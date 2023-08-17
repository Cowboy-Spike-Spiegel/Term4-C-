/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton_signup;
    QLabel *label_account;
    QLineEdit *lineEdit_account;
    QLabel *label_password;
    QPushButton *pushButton_signinAsUser;
    QLineEdit *lineEdit_password;
    QPushButton *pushButton_signinAsCourier;
    QPushButton *pushButton_signinAsAdmin;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(600, 200);
        Widget->setStyleSheet(QString::fromUtf8(""));
        pushButton_signup = new QPushButton(Widget);
        pushButton_signup->setObjectName(QString::fromUtf8("pushButton_signup"));
        pushButton_signup->setGeometry(QRect(450, 50, 130, 50));
        label_account = new QLabel(Widget);
        label_account->setObjectName(QString::fromUtf8("label_account"));
        label_account->setGeometry(QRect(20, 10, 130, 50));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        label_account->setFont(font);
        label_account->setAlignment(Qt::AlignCenter);
        lineEdit_account = new QLineEdit(Widget);
        lineEdit_account->setObjectName(QString::fromUtf8("lineEdit_account"));
        lineEdit_account->setGeometry(QRect(155, 15, 250, 40));
        label_password = new QLabel(Widget);
        label_password->setObjectName(QString::fromUtf8("label_password"));
        label_password->setGeometry(QRect(20, 60, 130, 50));
        label_password->setFont(font);
        label_password->setAlignment(Qt::AlignCenter);
        pushButton_signinAsUser = new QPushButton(Widget);
        pushButton_signinAsUser->setObjectName(QString::fromUtf8("pushButton_signinAsUser"));
        pushButton_signinAsUser->setGeometry(QRect(20, 130, 180, 50));
        lineEdit_password = new QLineEdit(Widget);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(155, 65, 250, 40));
        lineEdit_password->setEchoMode(QLineEdit::Password);
        pushButton_signinAsCourier = new QPushButton(Widget);
        pushButton_signinAsCourier->setObjectName(QString::fromUtf8("pushButton_signinAsCourier"));
        pushButton_signinAsCourier->setGeometry(QRect(210, 130, 180, 50));
        pushButton_signinAsAdmin = new QPushButton(Widget);
        pushButton_signinAsAdmin->setObjectName(QString::fromUtf8("pushButton_signinAsAdmin"));
        pushButton_signinAsAdmin->setGeometry(QRect(400, 130, 180, 50));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        pushButton_signup->setText(QCoreApplication::translate("Widget", "sign up", nullptr));
        label_account->setText(QCoreApplication::translate("Widget", "Account", nullptr));
        label_password->setText(QCoreApplication::translate("Widget", "Password", nullptr));
        pushButton_signinAsUser->setText(QCoreApplication::translate("Widget", "Signin as User", nullptr));
        pushButton_signinAsCourier->setText(QCoreApplication::translate("Widget", "Signin as Courier", nullptr));
        pushButton_signinAsAdmin->setText(QCoreApplication::translate("Widget", "Signin as Admin", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
