#-------------------------------------------------
#
# Project created by QtCreator 2016-01-07T16:40:49
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FMP Server
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    videothread.cpp \
    volttrethread.cpp

HEADERS  += widget.h \
    videothread.h \
    volttrethread.h

FORMS    += widget.ui

CONFIG += C++11

RESOURCES += \
    image.qrc
