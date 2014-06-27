#-------------------------------------------------
#
# Project created by QtCreator 2014-05-27T21:01:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia printsupport

TARGET = CurrencyExchangeProgram01
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    qcustomplot.cpp

HEADERS  += widget.h \
    qcustomplot.h

FORMS    += widget.ui

RESOURCES += \
    sound.qrc
