#-------------------------------------------------
#
# Project created by QtCreator 2017-03-07T18:43:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kg
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    projectscene.cpp \
    complexscene.cpp \
    cpoint.cpp

HEADERS  += widget.h \
    projectscene.h \
    complexscene.h \
    cpoint.h

FORMS    += widget.ui
