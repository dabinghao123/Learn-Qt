#-------------------------------------------------
#
# Project created by QtCreator 2016-01-05T16:13:04
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 04_TCPFile
TEMPLATE = app

SOURCES += main.cpp\
    serverwidget.cpp \
    clientwidget.cpp

HEADERS  += serverwidget.h \
    clientwidget.h

FORMS    += serverwidget.ui \
    clientwidget.ui

CONFIG += C++11
