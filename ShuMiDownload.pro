#-------------------------------------------------
#
# Project created by QtCreator 2016-11-05T12:33:15
#
#-------------------------------------------------

QT       += core gui
QT       += xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShuMiDownload
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    readxml.cpp \
    urloperation.cpp \
    ParserDom.cc \
    ParserSax.cc \
    Node.cc \
    ParserSax.tcc

HEADERS  += mainwindow.h \
    readxml.h \
    urloperation.h \
    ParserDom.h \
    ParserSax.h \
    Node.h \
    wincstring.h \
    debug.h

DISTFILES +=

