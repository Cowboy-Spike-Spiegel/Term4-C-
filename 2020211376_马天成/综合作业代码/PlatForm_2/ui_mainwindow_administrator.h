/********************************************************************************
** Form generated from reading UI file 'mainwindow_administrator.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_ADMINISTRATOR_H
#define UI_MAINWINDOW_ADMINISTRATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow_Administrator
{
public:
    QAction *action_findDelivery;
    QAction *action_show;
    QAction *action_update;
    QAction *action_findUser;
    QAction *action_allocate;
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page_findDelivery;
    QPushButton *pushButton_findDelivery;
    QTextEdit *textEdit_findDelivery;
    QPushButton *pushButton_findRefresh;
    QComboBox *comboBox_deliverySelect;
    QLineEdit *lineEdit_deliveryInput;
    QWidget *page_findUser;
    QTextEdit *textEdit_findUser;
    QLineEdit *lineEdit_findUser;
    QPushButton *pushButton_findUser;
    QWidget *page_allocate;
    QGroupBox *groupBox;
    QComboBox *comboBox_courier;
    QPushButton *pushButton_allocate;
    QPushButton *pushButton_delete;
    QWidget *page_show;
    QLabel *label_name;
    QLabel *label_account;
    QLabel *label_tel;
    QLabel *label_balance;
    QPushButton *pushButton_refreshShow;
    QMenuBar *menubar;
    QMenu *menu_service;
    QMenu *menu_information;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow_Administrator)
    {
        if (MainWindow_Administrator->objectName().isEmpty())
            MainWindow_Administrator->setObjectName(QString::fromUtf8("MainWindow_Administrator"));
        MainWindow_Administrator->resize(1200, 900);
        action_findDelivery = new QAction(MainWindow_Administrator);
        action_findDelivery->setObjectName(QString::fromUtf8("action_findDelivery"));
        action_show = new QAction(MainWindow_Administrator);
        action_show->setObjectName(QString::fromUtf8("action_show"));
        action_update = new QAction(MainWindow_Administrator);
        action_update->setObjectName(QString::fromUtf8("action_update"));
        action_findUser = new QAction(MainWindow_Administrator);
        action_findUser->setObjectName(QString::fromUtf8("action_findUser"));
        action_allocate = new QAction(MainWindow_Administrator);
        action_allocate->setObjectName(QString::fromUtf8("action_allocate"));
        centralwidget = new QWidget(MainWindow_Administrator);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 1200, 876));
        QFont font;
        font.setBold(true);
        stackedWidget->setFont(font);
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        page_findDelivery = new QWidget();
        page_findDelivery->setObjectName(QString::fromUtf8("page_findDelivery"));
        page_findDelivery->setStyleSheet(QString::fromUtf8("background-image: url(:/background/pics/3.png);"));
        pushButton_findDelivery = new QPushButton(page_findDelivery);
        pushButton_findDelivery->setObjectName(QString::fromUtf8("pushButton_findDelivery"));
        pushButton_findDelivery->setGeometry(QRect(960, 740, 141, 41));
        textEdit_findDelivery = new QTextEdit(page_findDelivery);
        textEdit_findDelivery->setObjectName(QString::fromUtf8("textEdit_findDelivery"));
        textEdit_findDelivery->setGeometry(QRect(100, 100, 1000, 600));
        pushButton_findRefresh = new QPushButton(page_findDelivery);
        pushButton_findRefresh->setObjectName(QString::fromUtf8("pushButton_findRefresh"));
        pushButton_findRefresh->setGeometry(QRect(0, 0, 151, 41));
        comboBox_deliverySelect = new QComboBox(page_findDelivery);
        comboBox_deliverySelect->setObjectName(QString::fromUtf8("comboBox_deliverySelect"));
        comboBox_deliverySelect->setGeometry(QRect(100, 740, 211, 41));
        lineEdit_deliveryInput = new QLineEdit(page_findDelivery);
        lineEdit_deliveryInput->setObjectName(QString::fromUtf8("lineEdit_deliveryInput"));
        lineEdit_deliveryInput->setGeometry(QRect(310, 740, 131, 41));
        stackedWidget->addWidget(page_findDelivery);
        page_findUser = new QWidget();
        page_findUser->setObjectName(QString::fromUtf8("page_findUser"));
        page_findUser->setStyleSheet(QString::fromUtf8("background-image: url(:/background/pics/3.png);"));
        textEdit_findUser = new QTextEdit(page_findUser);
        textEdit_findUser->setObjectName(QString::fromUtf8("textEdit_findUser"));
        textEdit_findUser->setGeometry(QRect(100, 100, 1000, 600));
        lineEdit_findUser = new QLineEdit(page_findUser);
        lineEdit_findUser->setObjectName(QString::fromUtf8("lineEdit_findUser"));
        lineEdit_findUser->setGeometry(QRect(760, 770, 171, 51));
        pushButton_findUser = new QPushButton(page_findUser);
        pushButton_findUser->setObjectName(QString::fromUtf8("pushButton_findUser"));
        pushButton_findUser->setGeometry(QRect(960, 770, 141, 51));
        stackedWidget->addWidget(page_findUser);
        page_allocate = new QWidget();
        page_allocate->setObjectName(QString::fromUtf8("page_allocate"));
        page_allocate->setStyleSheet(QString::fromUtf8("background-image: url(:/background/pics/3.png);"));
        groupBox = new QGroupBox(page_allocate);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(100, 100, 1000, 600));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft Yi Baiti"));
        font1.setPointSize(16);
        font1.setBold(true);
        groupBox->setFont(font1);
        groupBox->setStyleSheet(QString::fromUtf8(""));
        comboBox_courier = new QComboBox(page_allocate);
        comboBox_courier->setObjectName(QString::fromUtf8("comboBox_courier"));
        comboBox_courier->setGeometry(QRect(690, 740, 281, 41));
        pushButton_allocate = new QPushButton(page_allocate);
        pushButton_allocate->setObjectName(QString::fromUtf8("pushButton_allocate"));
        pushButton_allocate->setGeometry(QRect(1010, 740, 93, 41));
        pushButton_delete = new QPushButton(page_allocate);
        pushButton_delete->setObjectName(QString::fromUtf8("pushButton_delete"));
        pushButton_delete->setGeometry(QRect(880, 780, 93, 29));
        stackedWidget->addWidget(page_allocate);
        page_show = new QWidget();
        page_show->setObjectName(QString::fromUtf8("page_show"));
        page_show->setStyleSheet(QString::fromUtf8("background-image: url(:/background/pics/Eula.png);"));
        label_name = new QLabel(page_show);
        label_name->setObjectName(QString::fromUtf8("label_name"));
        label_name->setGeometry(QRect(100, 180, 200, 50));
        label_account = new QLabel(page_show);
        label_account->setObjectName(QString::fromUtf8("label_account"));
        label_account->setGeometry(QRect(100, 90, 200, 50));
        label_tel = new QLabel(page_show);
        label_tel->setObjectName(QString::fromUtf8("label_tel"));
        label_tel->setGeometry(QRect(100, 280, 200, 50));
        label_balance = new QLabel(page_show);
        label_balance->setObjectName(QString::fromUtf8("label_balance"));
        label_balance->setGeometry(QRect(100, 370, 200, 50));
        pushButton_refreshShow = new QPushButton(page_show);
        pushButton_refreshShow->setObjectName(QString::fromUtf8("pushButton_refreshShow"));
        pushButton_refreshShow->setGeometry(QRect(0, 0, 200, 70));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(true);
        pushButton_refreshShow->setFont(font2);
        pushButton_refreshShow->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        stackedWidget->addWidget(page_show);
        MainWindow_Administrator->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow_Administrator);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1200, 26));
        menu_service = new QMenu(menubar);
        menu_service->setObjectName(QString::fromUtf8("menu_service"));
        menu_information = new QMenu(menubar);
        menu_information->setObjectName(QString::fromUtf8("menu_information"));
        MainWindow_Administrator->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow_Administrator);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow_Administrator->setStatusBar(statusbar);

        menubar->addAction(menu_service->menuAction());
        menubar->addAction(menu_information->menuAction());
        menu_service->addAction(action_findDelivery);
        menu_service->addAction(action_findUser);
        menu_service->addAction(action_allocate);
        menu_information->addAction(action_show);

        retranslateUi(MainWindow_Administrator);

        QMetaObject::connectSlotsByName(MainWindow_Administrator);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow_Administrator)
    {
        MainWindow_Administrator->setWindowTitle(QCoreApplication::translate("MainWindow_Administrator", "MainWindow", nullptr));
        action_findDelivery->setText(QCoreApplication::translate("MainWindow_Administrator", "\346\237\245\350\257\242\345\277\253\351\200\222", nullptr));
        action_show->setText(QCoreApplication::translate("MainWindow_Administrator", "\345\261\225\347\244\272", nullptr));
        action_update->setText(QCoreApplication::translate("MainWindow_Administrator", "\344\277\256\346\224\271", nullptr));
        action_findUser->setText(QCoreApplication::translate("MainWindow_Administrator", "\346\237\245\350\257\242\347\224\250\346\210\267", nullptr));
        action_allocate->setText(QCoreApplication::translate("MainWindow_Administrator", "\345\210\206\351\205\215\345\277\253\351\200\222\345\221\230", nullptr));
        pushButton_findDelivery->setText(QCoreApplication::translate("MainWindow_Administrator", "\346\237\245\350\257\242", nullptr));
        pushButton_findRefresh->setText(QCoreApplication::translate("MainWindow_Administrator", "\345\205\250\351\203\250\345\210\267\346\226\260", nullptr));
        pushButton_findUser->setText(QCoreApplication::translate("MainWindow_Administrator", "\346\237\245\350\257\242", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow_Administrator", "\351\200\211\346\213\251\345\277\253\351\200\222", nullptr));
        pushButton_allocate->setText(QCoreApplication::translate("MainWindow_Administrator", "\345\210\206\351\205\215", nullptr));
        pushButton_delete->setText(QCoreApplication::translate("MainWindow_Administrator", "\345\210\240\351\231\244", nullptr));
        label_name->setText(QString());
        label_account->setText(QString());
        label_tel->setText(QString());
        label_balance->setText(QString());
        pushButton_refreshShow->setText(QCoreApplication::translate("MainWindow_Administrator", "\345\210\267\346\226\260", nullptr));
        menu_service->setTitle(QCoreApplication::translate("MainWindow_Administrator", "\346\234\215\345\212\241", nullptr));
        menu_information->setTitle(QCoreApplication::translate("MainWindow_Administrator", "\344\270\252\344\272\272\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow_Administrator: public Ui_MainWindow_Administrator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_ADMINISTRATOR_H
