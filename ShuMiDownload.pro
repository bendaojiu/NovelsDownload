#-------------------------------------------------
#
# Project created by QtCreator 2016-11-05T12:33:15
#
#-------------------------------------------------

QT       += core gui
QT       += xml network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShuMiDownload
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    readxml.cpp \
    urloperation.cpp \
    urlthread.cpp

HEADERS  += mainwindow.h \
    readxml.h \
    urloperation.h \
    urlthread.h

DISTFILES +=

