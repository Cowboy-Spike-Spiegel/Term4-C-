QT += core gui
QT += core gui sql
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Mythread.cpp \
    basic_Time.cpp \
    global.cpp \
    good.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow_administrator.cpp \
    mainwindow_courier.cpp \
    people.cpp \
    signup.cpp \
    widget.cpp

HEADERS += \
    Mythread.h \
    basic_Time.h \
    global.h \
    good.h \
    mainwindow.h \
    mainwindow_administrator.h \
    mainwindow_courier.h \
    people.h \
    signup.h \
    widget.h

FORMS += \
    mainwindow.ui \
    mainwindow_administrator.ui \
    mainwindow_courier.ui \
    signup.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
