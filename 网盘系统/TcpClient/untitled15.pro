#-------------------------------------------------
#
# Project created by QtCreator 2024-10-11T15:48:03
#
#-------------------------------------------------

QT       += core gui network
CONFIG += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled15
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connectmainwindow.cpp \
    userscoket.cpp

HEADERS  += mainwindow.h \
    connectmainwindow.h \
    userscoket.h

FORMS    += mainwindow.ui \
    connectmainwindow.ui
