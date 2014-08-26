TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += core dbus
SOURCES += main.cpp


DESTDIR = $$PWD/../../output
LIBS += -L$$PWD/../../output -lnapd

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib
