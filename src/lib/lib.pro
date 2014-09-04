#-------------------------------------------------
#
# Project created by QtCreator 2014-08-26T15:08:23
#
#-------------------------------------------------

QT       += core dbus

QT       -= gui

include (../Common.pri)

TARGET = napd
TEMPLATE = lib
DESTDIR = $$PWD/../../output
SOURCES += \
    collection/CheckedProcesses.cpp \
    collection/CustomChecks.cpp \
    collection/CheckedUnits.cpp \
    PowerManager.cpp \
    ProcessHandler.cpp \
    NapDaemon.cpp \
    Settings.cpp \
    collection/CheckedPIDs.cpp \
    DBusManager.cpp

HEADERS +=\
    collection/CheckedProcesses.h \
    Settings.h \
    collection/CustomChecks.h \
    checkable/Checkable.h \
    checkable/Process.h \
    checkable/CustomCheck.h \
    collection/Collection.h \
    checkable/Unit.h \
    collection/CheckedUnits.h \
    PowerManager.h \
    ProcessHandler.h \
    NotReadyException.h \
    NapDaemon.h \
    checkable/PID.h \
    collection/CheckedPIDs.h \
    DBusManager.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
