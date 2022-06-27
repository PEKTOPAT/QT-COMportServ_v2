#-------------------------------------------------
#
# Project created by QtCreator 2022-06-22T16:17:22
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = comPortGenerate_v2
TEMPLATE = app


SOURCES += main.cpp\
        generatedata_2.cpp

HEADERS  += generatedata_2.h

FORMS    += generatedata_2.ui

RESOURCES +=
RC_FILE = server.rc
