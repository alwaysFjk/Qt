#-------------------------------------------------
#
# Project created by QtCreator 2019-01-07T14:59:53
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += core gui xml
QT       += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetworkManage_Server_1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    settingdialog.cpp \
    adduserdialog.cpp \
    settingdialog_add.cpp \
    xmlhelp.cpp \
    billdialog.cpp

HEADERS  += mainwindow.h \
    settingdialog.h \
    adduserdialog.h \
    settingdialog_add.h \
    xmlhelp.h \
    billdialog.h

FORMS    += mainwindow.ui \
    settingdialog.ui \
    adduserdialog.ui \
    settingdialog_add.ui \
    billdialog.ui
