#-------------------------------------------------
#
# Project created by QtCreator 2016-05-06T15:41:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Taxi-Pooling
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    taxicell.cpp

HEADERS  += mainwindow.h \
    taxicell.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
