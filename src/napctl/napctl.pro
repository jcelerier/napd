#-------------------------------------------------
#
# Project created by QtCreator 2014-09-01T11:16:31
#
#-------------------------------------------------

QT       += core dbus

QT       -= gui

include (../Common.pri)

TARGET = napctl
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = $$PWD/../../output

SOURCES += main.cpp \
    NapCtl.cpp

HEADERS += \
    NapCtl.h
