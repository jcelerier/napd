TEMPLATE = app

include (../Common.pri)

CONFIG += console
CONFIG -= app_bundle
QT += core dbus
SOURCES += main.cpp
TARGET=napd

DESTDIR = $$PWD/../../output
LIBS += -L$$PWD/../../output -lnapd

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib
