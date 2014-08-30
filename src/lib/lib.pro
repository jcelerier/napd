#-------------------------------------------------
#
# Project created by QtCreator 2014-08-26T15:08:23
#
#-------------------------------------------------

QT       += core dbus

QT       -= gui

QMAKE_CXXFLAGS += -std=c++14

TARGET = napd
TEMPLATE = lib
DESTDIR = $$PWD/../../output
SOURCES += \
    CheckedProcesses.cpp \
    CustomChecks.cpp \
    CheckedUnits.cpp \
    PowerManager.cpp \
    ProcessHandler.cpp \
    NapDaemon.cpp \
    Settings.cpp

HEADERS +=\
    CheckedProcesses.h \
    Settings.h \
    CustomChecks.h \
    checkable/Checkable.h \
    checkable/Process.h \
    checkable/CustomCheck.h \
    collection/Collection.h \
    checkable/Unit.h \
    CheckedUnits.h \
    PowerManager.h \
    ProcessHandler.h \
    NotReadyException.h \
    NapDaemon.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
