QT += core serialport
QT -= gui

TARGET = simpleSerialCom
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    serialcom.cpp

HEADERS += \
    serialcom.h

