/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_receive;
    QAction *action_send;
    QAction *action_show;
    QAction *action_update;
    QAction *action_find;
    QAction *action_recharge;
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page_receive;
    QPushButton *pushButton_receive1;
    QLabel *label_receive1;
    QLabel *label_receive2;
    QLabel *label_receive3;
    QLabel *label_receive4;
    QLabel *label_receive5;
    QLabel *label_receive6;
    QLabel *label_receive7;
    QPushButton *pushButton_receive2;
    QPushButton *pushButton_receive3;
    QPushButton *pushButton_receive4;
    QPushButton *pushButton_receive5;
    QPushButton *pushButton_receive6;
    QPushButton *pushButton_receive7;
    QPushButton *pushButton_receiveup;
    QPushButton *pushButton_receivedown;
    QLabel *label_receivePage;
    QLineEdit *lineEdit_receivePage;
    QLabel *label_receive8;
    QLabel *label_receive9;
    QLabel *label_receive10;
    QPushButton *pushButton_receive9;
    QPushButton *pushButton_receive8;
    QPushButton *pushButton_receive10;
    QLabel *label_recTitle;
    QWidget *page_send;
    QPushButton *pushButton_send;
    QComboBox *comboBox_sendUsers;
    QLineEdit *lineEdit_sendDiscription;
    QLabel *label_sendDiscription;
    QComboBox *comboBox_sendItem;
    QComboBox *comboBox_SendWeight;
    QWidget *page_history;
    QLabel *label_allTitle;
    QLabel *label_all1;
    QLabel *label_all2;
    QLabel *label_all3;
    QLabel *label_all4;
    QLabel *label_all5;
    QLabel *label_all6;
    QLabel *label_all7;
    QLabel *label_all8;
    QLabel *label_all9;
    QLabel *label_all10;
    QPushButton *pushButton_allSend;
    QPushButton *pushButton_allReceive;
    QPushButton *pushButton_allup;
    QPushButton *pushButton_alldown;
    QLabel *label_allPage;
    QLineEdit *lineEdit_allPage;
    QComboBox *comboBox_allSelect;
    QComboBox *comboBox_allSuggest;
    QDateEdit *dateEdit_allSuggest;
    QPushButton *pushButton_find;
    QPushButton *pushButton_allRefresh;
    QLineEdit *lineEdit_allSuggest;
    QWidget *page_recharge;
    QPushButton *pushButton_recharge;
    QComboBox *comboBox_recharge;
    QLineEdit *lineEdit_recharge;
    QWidget *page_show;
    QLabel *label_showAddress;
    QLabel *label_showAccount;
    QLabel *label_showTel;
    QLabel *label_showName;
    QLabel *label_showBalance;
    QPushButton *pushButton;
    QWidget *page_update;
    QLineEdit *lineEdit_updateName;
    QLineEdit *lineEdit_updateTel;
    QLineEdit *lineEdit_updateAddress;
    QPushButton *pushButton_update;
    QLineEdit *lineEdit_updatePassword;
    QMenuBar *menubar;
    QMenu *menu_service;
    QMenu *menu_information;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1200, 900);
        action_receive = new QAction(MainWindow);
        action_receive->setObjectName(QString::fromUtf8("action_receive"));
        action_send = new QAction(MainWindow);
        action_send->setObjectName(QString::fromUtf8("action_send"));
        action_show = new QAction(MainWindow);
        action_show->setObjectName(QString::fromUtf8("action_show"));
        action_update = new QAction(MainWindow);
        action_update->setObjectName(QString::fromUtf8("action_update"));
        action_find = new QAction(MainWindow);
        action_find->setObjectName(QString::fromUtf8("action_find"));
        action_recharge = new QAction(MainWindow);
        action_recharge->setObjectName(QString::fromUtf8("action_recharge"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 1200, 876));
        page_receive = new QWidget();
        page_receive->setObjectName(QString::fromUtf8("page_receive"));
        page_receive->setStyleSheet(QString::fromUtf8("background-image: url(:/background/pics/3.png);"));
        pushButton_receive1 = new QPushButton(page_receive);
        pushButton_receive1->setObjectName(QString::fromUtf8("pushButton_receive1"));
        pushButton_receive1->setGeometry(QRect(1000, 150, 100, 45));
        label_receive1 = new QLabel(page_receive);
        label_receive1->setObjectName(QString::fromUtf8("label_receive1"));
        label_receive1->setGeometry(QRect(100, 150, 900, 45));
        label_receive2 = new QLabel(page_receive);
        label_receive2->setObjectName(QString::fromUtf8("label_receive2"));
        label_receive2->setGeometry(QRect(100, 200, 900, 45));
        label_receive3 = new QLabel(page_receive);
        label_receive3->setObjectName(QString::fromUtf8("label_receive3"));
        label_receive3->setGeometry(QRect(100, 250, 900, 45));
        label_receive4 = new QLabel(page_receive);
        label_receive4->setObjectName(QString::fromUtf8("label_receive4"));
        label_receive4->setGeometry(QRect(100, 300, 900, 45));
        label_receive5 = new QLabel(page_receive);
        label_receive5->setObjectName(QString::fromUtf8("label_receive5"));
        label_receive5->setGeometry(QRect(100, 350, 900, 45));
        label_receive6 = new QLabel(page_receive);
        label_receive6->setObjectName(QString::fromUtf8("label_receive6"));
        label_receive6->setGeometry(QRect(100, 400, 900, 45));
        label_receive7 = new QLabel(page_receive);
        label_receive7->setObjectName(QString::fromUtf8("label_receive7"));
        label_receive7->setGeometry(QRect(100, 450, 900, 45));
        pushButton_receive2 = new QPushButton(page_receive);
        pushButton_receive2->setObjectName(QString::fromUtf8("pushButton_receive2"));
        pushButton_receive2->setGeometry(QRect(1000, 200, 100, 45));
        pushButton_receive3 = new QPushButton(page_receive);
        pushButton_receive3->setObjectName(QString::fromUtf8("pushButton_receive3"));
        pushButton_receive3->setGeometry(QRect(1000, 250, 100, 45));
        pushButton_receive4 = new QPushButton(page_receive);
        pushButton_receive4->setObjectName(QString::fromUtf8("pushButton_receive4"));
        pushButton_receive4->setGeometry(QRect(1000, 300, 100, 45));
        pushButton_receive5 = new QPushButton(page_receive);
        pushButton_receive5->setObjectName(QString::fromUtf8("pushButton_receive5"));
        pushButton_receive5->setGeometry(QRect(1000, 350, 100, 45));
        pushButton_receive6 = new QPushButton(page_receive);
        pushButton_receive6->setObjectName(QString::fromUtf8("pushButton_receive6"));
        pushButton_receive6->setGeometry(QRect(1000, 400, 100, 45));
        pushButton_receive7 = new QPushButton(page_receive);
        pushButton_receive7->setObjectName(QString::fromUtf8("pushButton_receive7"));
        pushButton_receive7->setGeometry(QRect(1000, 450, 100, 45));
        pushButton_receiveup = new QPushButton(page_receive);
        pushButton_receiveup->setObjectName(QString::fromUtf8("pushButton_receiveup"));
        pushButton_receiveup->setGeometry(QRect(450, 760, 80, 30));
        pushButton_receivedown = new QPushButton(page_receive);
        pushButton_receivedown->setObjectName(QString::fromUtf8("pushButton_receivedown"));
        pushButton_receivedown->setGeometry(QRect(670, 760, 80, 30));
        label_receivePage = new QLabel(page_receive);
        label_receivePage->setObjectName(QString::fromUtf8("label_receivePage"));
        label_receivePage->setGeometry(QRect(530, 760, 80, 30));
        label_receivePage->setAlignment(Qt::AlignCenter);
        lineEdit_receivePage = new QLineEdit(page_receive);
        lineEdit_receivePage->setObjectName(QString::fromUtf8("lineEdit_receivePage"));
        lineEdit_receivePage->setGeometry(QRect(610, 760, 60, 30));
        label_receive8 = new QLabel(page_receive);
        label_receive8->setObjectName(QString::fromUtf8("label_receive8"));
        label_receive8->setGeometry(QRect(100, 500, 900, 45));
        label_receive9 = new QLabel(page_receive);
        label_receive9->setObjectName(QString::fromUtf8("label_receive9"));
        label_receive9->setGeometry(QRect(100, 550, 900, 45));
        label_receive10 = new QLabel(page_receive);
        label_receive10->setObjectName(QString::fromUtf8("label_receive10"));
        label_receive10->setGeometry(QRect(100, 600, 900, 45));
        pushButton_receive9 = new QPushButton(page_receive);
        pushButton_receive9->setObjectName(QString::fromUtf8("pushButton_receive9"));
        pushButton_receive9->setGeometry(QRect(1000, 500, 100, 45));
        pushButton_receive8 = new QPushButton(page_receive);
        pushButton_receive8->setObjectName(QString::fromUtf8("pushButton_receive8"));
        pushButton_receive8->setGeometry(QRect(1000, 550, 100, 45));
        pushButton_receive10 = new QPushButton(page_receive);
        pushButton_receive10->setObjectName(QString::fromUtf8("pushButton_receive10"));
        pushButton_receive10->setGeometry(QRect(1000, 600, 100, 45));
        label_recTitle = new QLabel(page_receive);
        label_recTitle->setObjectName(QString::fromUtf8("label_recTitle"));
        label_recTitle->setGeometry(QRect(100, 100, 900, 45));
        stackedWidget->addWidget(page_receive);
        page_send = new QWidget();
        page_send->setObjectName(QString::fromUtf8("page_send"));
        page_send->setStyleSheet(QString::fromUtf8("background-image: url(:/background/pics/Eula.png);"));
        pushButton_send = new QPushButton(page_send);
        pushButton_send->setObjectName(QString::fromUtf8("pushButton_send"));
        pushButton_send->setGeometry(QRect(250, 450, 100, 50));
        comboBox_sendUsers = new QComboBox(page_send);
        comboBox_sendUsers->setObjectName(QString::fromUtf8("comboBox_sendUsers"));
        comboBox_sendUsers->setGeometry(QRect(150, 140, 300, 50));
        lineEdit_sendDiscription = new QLineEdit(page_send);
        lineEdit_sendDiscription->setObjectName(QString::fromUtf8("lineEdit_sendDiscription"));
        lineEdit_sendDiscription->setGeometry(QRect(150, 350, 300, 50));
        label_sendDiscription = new QLabel(page_send);
        label_sendDiscription->setObjectName(QString::fromUtf8("label_sendDiscription"));
        label_sendDiscription->setGeometry(QRect(150, 319, 101, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label_sendDiscription->setFont(font);
        label_sendDiscription->setAlignment(Qt::AlignCenter);
        comboBox_sendItem = new QComboBox(page_send);
        comboBox_sendItem->addItem(QString());
        comboBox_sendItem->addItem(QString());
        comboBox_sendItem->addItem(QString());
        comboBox_sendItem->setObjectName(QString::fromUtf8("comboBox_sendItem"));
        comboBox_sendItem->setGeometry(QRect(150, 240, 180, 50));
        comboBox_SendWeight = new QComboBox(page_send);
        comboBox_SendWeight->addItem(QString());
        comboBox_SendWeight->addItem(QString());
        comboBox_SendWeight->addItem(QString());
        comboBox_SendWeight->addItem(QString());
        comboBox_SendWeight->addItem(QString());
        comboBox_SendWeight->addItem(QString());
        comboBox_SendWeight->addItem(QString());
        comboBox_SendWeight->addItem(QString());
        comboBox_SendWeight->addItem(QString());
        comboBox_SendWeight->addItem(QString());
        comboBox_SendWeight->setObjectName(QString::fromUtf8("comboBox_SendWeight"));
        comboBox_SendWeight->setGeometry(QRect(330, 240, 120, 50));
        stackedWidget->addWidget(page_send);
        page_history = new QWidget();
        page_history->setObjectName(QString::fromUtf8("page_history"));
        page_history->setStyleSheet(QString::fromUtf8("background-image: url(:/background/pics/3.png);"));
        label_allTitle = new QLabel(page_history);
        label_allTitle->setObjectName(QString::fromUtf8("label_allTitle"));
        label_allTitle->setGeometry(QRect(100, 80, 1000, 45));
        label_all1 = new QLabel(page_history);
        label_all1->setObjectName(QString::fromUtf8("label_all1"));
        label_all1->setGeometry(QRect(100, 130, 1000, 45));
        label_all2 = new QLabel(page_history);
        label_all2->setObjectName(QString::fromUtf8("label_all2"));
        label_all2->setGeometry(QRect(100, 180, 1000, 45));
        label_all3 = new QLabel(page_history);
        label_all3->setObjectName(QString::fromUtf8("label_all3"));
        label_all3->setGeometry(QRect(100, 230, 1000, 45));
        label_all4 = new QLabel(page_history);
        label_all4->setObjectName(QString::fromUtf8("label_all4"));
        label_all4->setGeometry(QRect(100, 280, 1000, 45));
        label_all5 = new QLabel(page_history);
        label_all5->setObjectName(QString::fromUtf8("label_all5"));
        label_all5->setGeometry(QRect(100, 330, 1000, 45));
        label_all6 = new QLabel(page_history);
        label_all6->setObjectName(QString::fromUtf8("label_all6"));
        label_all6->setGeometry(QRect(100, 380, 1000, 45));
        label_all7 = new QLabel(page_history);
        label_all7->setObjectName(QString::fromUtf8("label_all7"));
        label_all7->setGeometry(QRect(100, 430, 1000, 45));
        label_all8 = new QLabel(page_history);
        label_all8->setObjectName(QString::fromUtf8("label_all8"));
        label_all8->setGeometry(QRect(100, 480, 1000, 45));
        label_all9 = new QLabel(page_history);
        label_all9->setObjectName(QString::fromUtf8("label_all9"));
        label_all9->setGeometry(QRect(100, 530, 1000, 45));
        label_all10 = new QLabel(page_history);
        label_all10->setObjectName(QString::fromUtf8("label_all10"));
        label_all10->setGeometry(QRect(100, 580, 1000, 45));
        pushButton_allSend = new QPushButton(page_history);
        pushButton_allSend->setObjectName(QString::fromUtf8("pushButton_allSend"));
        pushButton_allSend->setGeometry(QRect(100, 700, 150, 50));
        pushButton_allReceive = new QPushButton(page_history);
        pushButton_allReceive->setObjectName(QString::fromUtf8("pushButton_allReceive"));
        pushButton_allReceive->setGeometry(QRect(250, 700, 150, 50));
        pushButton_allup = new QPushButton(page_history);
        pushButton_allup->setObjectName(QString::fromUtf8("pushButton_allup"));
        pushButton_allup->setGeometry(QRect(800, 630, 80, 30));
        pushButton_alldown = new QPushButton(page_history);
        pushButton_alldown->setObjectName(QString::fromUtf8("pushButton_alldown"));
        pushButton_alldown->setGeometry(QRect(1020, 630, 80, 30));
        label_allPage = new QLabel(page_history);
        label_allPage->setObjectName(QString::fromUtf8("label_allPage"));
        label_allPage->setGeometry(QRect(880, 630, 80, 30));
        label_allPage->setAlignment(Qt::AlignCenter);
        lineEdit_allPage = new QLineEdit(page_history);
        lineEdit_allPage->setObjectName(QString::fromUtf8("lineEdit_allPage"));
        lineEdit_allPage->setGeometry(QRect(960, 630, 60, 30));
        comboBox_allSelect = new QComboBox(page_history);
        comboBox_allSelect->addItem(QString());
        comboBox_allSelect->addItem(QString());
        comboBox_allSelect->addItem(QString());
        comboBox_allSelect->addItem(QString());
        comboBox_allSelect->setObjectName(QString::fromUtf8("comboBox_allSelect"));
        comboBox_allSelect->setGeometry(QRect(650, 700, 150, 50));
        comboBox_allSuggest = new QComboBox(page_history);
        comboBox_allSuggest->setObjectName(QString::fromUtf8("comboBox_allSuggest"));
        comboBox_allSuggest->setGeometry(QRect(800, 700, 150, 50));
        dateEdit_allSuggest = new QDateEdit(page_history);
        dateEdit_allSuggest->setObjectName(QString::fromUtf8("dateEdit_allSuggest"));
        dateEdit_allSuggest->setGeometry(QRect(800, 700, 150, 50));
        pushButton_find = new QPushButton(page_history);
        pushButton_find->setObjectName(QString::fromUtf8("pushButton_find"));
        pushButton_find->setGeometry(QRect(950, 700, 150, 50));
        pushButton_allRefresh = new QPushButton(page_history);
        pushButton_allRefresh->setObjectName(QString::fromUtf8("pushButton_allRefresh"));
        pushButton_allRefresh->setGeometry(QRect(0, 0, 150, 45));
        QFont font1;
        font1.setPointSize(12);
        pushButton_allRefresh->setFont(font1);
        pushButton_allRefresh->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_allSuggest = new QLineEdit(page_history);
        lineEdit_allSuggest->setObjectName(QString::fromUtf8("lineEdit_allSuggest"));
        lineEdit_allSuggest->setGeometry(QRect(800, 700, 150, 50));
        stackedWidget->addWidget(page_history);
        page_recharge = new QWidget();
        page_recharge->setObjectName(QString::fromUtf8("page_recharge"));
        page_recharge->setStyleSheet(QString::fromUtf8("background-image: url(:/background/pics/Eula.png);"));
        pushButton_recharge = new QPushButton(page_recharge);
        pushButton_recharge->setObjectName(QString::fromUtf8("pushButton_recharge"));
        pushButton_recharge->setGeometry(QRect(70, 190, 281, 50));
        comboBox_recharge = new QComboBox(page_recharge);
        comboBox_recharge->setObjectName(QString::fromUtf8("comboBox_recharge"));
        comboBox_recharge->setGeometry(QRect(200, 80, 150, 50));
        lineEdit_recharge = new QLineEdit(page_recharge);
        lineEdit_recharge->setObjectName(QString::fromUtf8("lineEdit_recharge"));
        lineEdit_recharge->setGeometry(QRect(70, 80, 131, 50));
        stackedWidget->addWidget(page_recharge);
        page_show = new QWidget();
        page_show->setObjectName(QString::fromUtf8("page_show"));
        page_show->setStyleSheet(QString::fromUtf8("background-image: url(:/background/pics/Eula.png);"));
        label_showAddress = new QLabel(page_show);
        label_showAddress->setObjectName(QString::fromUtf8("label_showAddress"));
        label_showAddress->setGeometry(QRect(100, 400, 400, 80));
        label_showAccount = new QLabel(page_show);
        label_showAccount->setObjectName(QString::fromUtf8("label_showAccount"));
        label_showAccount->setGeometry(QRect(100, 100, 400, 80));
        label_showTel = new QLabel(page_show);
        label_showTel->setObjectName(QString::fromUtf8("label_showTel"));
        label_showTel->setGeometry(QRect(100, 300, 400, 80));
        label_showName = new QLabel(page_show);
        label_showName->setObjectName(QString::fromUtf8("label_showName"));
        label_showName->setGeometry(QRect(100, 200, 400, 80));
        label_showBalance = new QLabel(page_show);
        label_showBalance->setObjectName(QString::fromUtf8("label_showBalance"));
        label_showBalance->setGeometry(QRect(100, 500, 400, 80));
        pushButton = new QPushButton(page_show);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(0, 0, 200, 70));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(true);
        pushButton->setFont(font2);
        pushButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        stackedWidget->addWidget(page_show);
        page_update = new QWidget();
        page_update->setObjectName(QString::fromUtf8("page_update"));
        page_update->setStyleSheet(QString::fromUtf8("background-image: url(:/background/pics/Eula.png);"));
        lineEdit_updateName = new QLineEdit(page_update);
        lineEdit_updateName->setObjectName(QString::fromUtf8("lineEdit_updateName"));
        lineEdit_updateName->setGeometry(QRect(100, 100, 300, 50));
        lineEdit_updateTel = new QLineEdit(page_update);
        lineEdit_updateTel->setObjectName(QString::fromUtf8("lineEdit_updateTel"));
        lineEdit_updateTel->setGeometry(QRect(100, 200, 300, 50));
        lineEdit_updateAddress = new QLineEdit(page_update);
        lineEdit_updateAddress->setObjectName(QString::fromUtf8("lineEdit_updateAddress"));
        lineEdit_updateAddress->setGeometry(QRect(100, 300, 300, 50));
        pushButton_update = new QPushButton(page_update);
        pushButton_update->setObjectName(QString::fromUtf8("pushButton_update"));
        pushButton_update->setGeometry(QRect(100, 500, 200, 50));
        lineEdit_updatePassword = new QLineEdit(page_update);
        lineEdit_updatePassword->setObjectName(QString::fromUtf8("lineEdit_updatePassword"));
        lineEdit_updatePassword->setGeometry(QRect(100, 400, 300, 50));
        stackedWidget->addWidget(page_update);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1200, 26));
        menu_service = new QMenu(menubar);
        menu_service->setObjectName(QString::fromUtf8("menu_service"));
        menu_information = new QMenu(menubar);
        menu_information->setObjectName(QString::fromUtf8("menu_information"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_service->menuAction());
        menubar->addAction(menu_information->menuAction());
        menu_service->addAction(action_receive);
        menu_service->addAction(action_send);
        menu_service->addAction(action_find);
        menu_service->addAction(action_recharge);
        menu_information->addAction(action_show);
        menu_information->addAction(action_update);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_receive->setText(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266\345\277\253\351\200\222", nullptr));
        action_send->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\345\277\253\351\200\222", nullptr));
        action_show->setText(QCoreApplication::translate("MainWindow", "\345\261\225\347\244\272", nullptr));
        action_update->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271", nullptr));
        action_find->setText(QCoreApplication::translate("MainWindow", "\345\216\206\345\217\262\345\277\253\351\200\222", nullptr));
        action_recharge->setText(QCoreApplication::translate("MainWindow", "\345\205\205\345\200\274", nullptr));
        pushButton_receive1->setText(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266", nullptr));
        label_receive1->setText(QString());
        label_receive2->setText(QString());
        label_receive3->setText(QString());
        label_receive4->setText(QString());
        label_receive5->setText(QString());
        label_receive6->setText(QString());
        label_receive7->setText(QString());
        pushButton_receive2->setText(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266", nullptr));
        pushButton_receive3->setText(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266", nullptr));
        pushButton_receive4->setText(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266", nullptr));
        pushButton_receive5->setText(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266", nullptr));
        pushButton_receive6->setText(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266", nullptr));
        pushButton_receive7->setText(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266", nullptr));
        pushButton_receiveup->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\270\200\351\241\265", nullptr));
        pushButton_receivedown->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\351\241\265", nullptr));
        label_receivePage->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_receive8->setText(QString());
        label_receive9->setText(QString());
        label_receive10->setText(QString());
        pushButton_receive9->setText(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266", nullptr));
        pushButton_receive8->setText(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266", nullptr));
        pushButton_receive10->setText(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266", nullptr));
        label_recTitle->setText(QString());
        pushButton_send->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        label_sendDiscription->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\346\217\217\350\277\260", nullptr));
        comboBox_sendItem->setItemText(0, QCoreApplication::translate("MainWindow", "\346\230\223\347\242\216\345\223\201", nullptr));
        comboBox_sendItem->setItemText(1, QCoreApplication::translate("MainWindow", "\344\271\246\346\234\254", nullptr));
        comboBox_sendItem->setItemText(2, QCoreApplication::translate("MainWindow", "\346\231\256\351\200\232\345\277\253\351\200\222", nullptr));

        comboBox_SendWeight->setItemText(0, QCoreApplication::translate("MainWindow", "1 kg", nullptr));
        comboBox_SendWeight->setItemText(1, QCoreApplication::translate("MainWindow", "2 kg", nullptr));
        comboBox_SendWeight->setItemText(2, QCoreApplication::translate("MainWindow", "3 kg", nullptr));
        comboBox_SendWeight->setItemText(3, QCoreApplication::translate("MainWindow", "4 kg", nullptr));
        comboBox_SendWeight->setItemText(4, QCoreApplication::translate("MainWindow", "5 kg", nullptr));
        comboBox_SendWeight->setItemText(5, QCoreApplication::translate("MainWindow", "6 kg", nullptr));
        comboBox_SendWeight->setItemText(6, QCoreApplication::translate("MainWindow", "7 kg", nullptr));
        comboBox_SendWeight->setItemText(7, QCoreApplication::translate("MainWindow", "8 kg", nullptr));
        comboBox_SendWeight->setItemText(8, QCoreApplication::translate("MainWindow", "9 kg", nullptr));
        comboBox_SendWeight->setItemText(9, QCoreApplication::translate("MainWindow", ">10 kg", nullptr));

        label_allTitle->setText(QString());
        label_all1->setText(QString());
        label_all2->setText(QString());
        label_all3->setText(QString());
        label_all4->setText(QString());
        label_all5->setText(QString());
        label_all6->setText(QString());
        label_all7->setText(QString());
        label_all8->setText(QString());
        label_all9->setText(QString());
        label_all10->setText(QString());
        pushButton_allSend->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242\345\217\221\351\200\201\345\216\206\345\217\262", nullptr));
        pushButton_allReceive->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242\346\216\245\346\224\266\345\216\206\345\217\262", nullptr));
        pushButton_allup->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\270\200\351\241\265", nullptr));
        pushButton_alldown->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\351\241\265", nullptr));
        label_allPage->setText(QString());
        comboBox_allSelect->setItemText(0, QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\344\272\272", nullptr));
        comboBox_allSelect->setItemText(1, QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266\344\272\272", nullptr));
        comboBox_allSelect->setItemText(2, QCoreApplication::translate("MainWindow", "\346\227\266\351\227\264", nullptr));
        comboBox_allSelect->setItemText(3, QCoreApplication::translate("MainWindow", "\345\215\225\345\217\267", nullptr));

        pushButton_find->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        pushButton_allRefresh->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260\345\205\250\351\203\250\350\256\260\345\275\225", nullptr));
        pushButton_recharge->setText(QCoreApplication::translate("MainWindow", "\345\205\205\345\200\274", nullptr));
        lineEdit_recharge->setText(QString());
        label_showAddress->setText(QString());
        label_showAccount->setText(QString());
        label_showTel->setText(QString());
        label_showName->setText(QString());
        label_showBalance->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        pushButton_update->setText(QCoreApplication::translate("MainWindow", "\346\233\264\346\226\260", nullptr));
        menu_service->setTitle(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241", nullptr));
        menu_information->setTitle(QCoreApplication::translate("MainWindow", "\344\270\252\344\272\272\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
