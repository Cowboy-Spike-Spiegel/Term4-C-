/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignUp
{
public:
    QLabel *label_name;
    QLabel *label_password;
    QLabel *label_tel;
    QLabel *label_address;
    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_password;
    QLineEdit *lineEdit_tel;
    QLineEdit *lineEdit_address;
    QPushButton *pushButton_user;
    QPushButton *pushButton_courier;

    void setupUi(QWidget *SignUp)
    {
        if (SignUp->objectName().isEmpty())
            SignUp->setObjectName(QString::fromUtf8("SignUp"));
        SignUp->resize(400, 300);
        label_name = new QLabel(SignUp);
        label_name->setObjectName(QString::fromUtf8("label_name"));
        label_name->setGeometry(QRect(10, 10, 130, 50));
        label_name->setAlignment(Qt::AlignCenter);
        label_password = new QLabel(SignUp);
        label_password->setObjectName(QString::fromUtf8("label_password"));
        label_password->setGeometry(QRect(10, 60, 130, 50));
        label_password->setAlignment(Qt::AlignCenter);
        label_tel = new QLabel(SignUp);
        label_tel->setObjectName(QString::fromUtf8("label_tel"));
        label_tel->setGeometry(QRect(10, 110, 130, 50));
        label_tel->setAlignment(Qt::AlignCenter);
        label_address = new QLabel(SignUp);
        label_address->setObjectName(QString::fromUtf8("label_address"));
        label_address->setGeometry(QRect(10, 160, 130, 50));
        label_address->setAlignment(Qt::AlignCenter);
        lineEdit_name = new QLineEdit(SignUp);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(140, 15, 250, 40));
        lineEdit_password = new QLineEdit(SignUp);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(140, 65, 250, 40));
        lineEdit_tel = new QLineEdit(SignUp);
        lineEdit_tel->setObjectName(QString::fromUtf8("lineEdit_tel"));
        lineEdit_tel->setGeometry(QRect(140, 115, 250, 40));
        lineEdit_address = new QLineEdit(SignUp);
        lineEdit_address->setObjectName(QString::fromUtf8("lineEdit_address"));
        lineEdit_address->setGeometry(QRect(140, 165, 250, 40));
        pushButton_user = new QPushButton(SignUp);
        pushButton_user->setObjectName(QString::fromUtf8("pushButton_user"));
        pushButton_user->setGeometry(QRect(20, 230, 170, 50));
        pushButton_courier = new QPushButton(SignUp);
        pushButton_courier->setObjectName(QString::fromUtf8("pushButton_courier"));
        pushButton_courier->setGeometry(QRect(210, 230, 170, 50));

        retranslateUi(SignUp);

        QMetaObject::connectSlotsByName(SignUp);
    } // setupUi

    void retranslateUi(QWidget *SignUp)
    {
        SignUp->setWindowTitle(QCoreApplication::translate("SignUp", "Form", nullptr));
        label_name->setText(QCoreApplication::translate("SignUp", "name", nullptr));
        label_password->setText(QCoreApplication::translate("SignUp", "password", nullptr));
        label_tel->setText(QCoreApplication::translate("SignUp", "tel", nullptr));
        label_address->setText(QCoreApplication::translate("SignUp", "address", nullptr));
        pushButton_user->setText(QCoreApplication::translate("SignUp", "Signup as User", nullptr));
        pushButton_courier->setText(QCoreApplication::translate("SignUp", "Signup as Courier", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignUp: public Ui_SignUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
