#-------------------------------------------------
#
# Project created by QtCreator 2016-05-06T15:41:29
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Taxi-Pooling
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cell.cpp \
    taxi.cpp \
    delaythread.cpp \
    customer.cpp

HEADERS  += mainwindow.h \
    cell.h \
    taxi.h \
    delaythread.h \
    customer.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
