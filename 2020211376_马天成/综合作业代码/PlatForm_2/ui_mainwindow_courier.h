/********************************************************************************
** Form generated from reading UI file 'mainwindow_courier.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_COURIER_H
#define UI_MAINWINDOW_COURIER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow_Courier
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QPushButton *pushButton_delivery;
    QPushButton *pushButton_reject;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow_Courier)
    {
        if (MainWindow_Courier->objectName().isEmpty())
            MainWindow_Courier->setObjectName(QString::fromUtf8("MainWindow_Courier"));
        MainWindow_Courier->resize(1200, 900);
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(16);
        font.setBold(true);
        MainWindow_Courier->setFont(font);
        centralwidget = new QWidget(MainWindow_Courier);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(100, 100, 1000, 600));
        pushButton_delivery = new QPushButton(centralwidget);
        pushButton_delivery->setObjectName(QString::fromUtf8("pushButton_delivery"));
        pushButton_delivery->setGeometry(QRect(900, 800, 150, 50));
        pushButton_reject = new QPushButton(centralwidget);
        pushButton_reject->setObjectName(QString::fromUtf8("pushButton_reject"));
        pushButton_reject->setGeometry(QRect(700, 800, 150, 50));
        MainWindow_Courier->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow_Courier);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow_Courier->setStatusBar(statusbar);

        retranslateUi(MainWindow_Courier);

        QMetaObject::connectSlotsByName(MainWindow_Courier);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow_Courier)
    {
        MainWindow_Courier->setWindowTitle(QCoreApplication::translate("MainWindow_Courier", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow_Courier", "\345\217\257\346\264\276\351\200\201\347\232\204\345\277\253\351\200\222", nullptr));
        pushButton_delivery->setText(QCoreApplication::translate("MainWindow_Courier", "\351\205\215\351\200\201", nullptr));
        pushButton_reject->setText(QCoreApplication::translate("MainWindow_Courier", "\346\213\222\347\273\235", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow_Courier: public Ui_MainWindow_Courier {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_COURIER_H
