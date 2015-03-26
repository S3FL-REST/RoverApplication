#-------------------------------------------------
#
# Project created by QtCreator 2015-03-25T11:58:01
#
#-------------------------------------------------

QT       += core serialport network multimedia

QT       -= gui

TARGET = RoverApplication
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Serial/serialport.cpp \
    robotmain.cpp \
    Serial/serialmanager.cpp \
    Controls/robotdrive.cpp \
    Protocols/rest_network.cpp \
    Network/networkserver.cpp \
    Network/networkdatamanager.cpp

HEADERS += \
    Serial/serialport.h \
    robotmain.h \
    Serial/serialmanager.h \
    Controls/robotdrive.h \
    Protocols/rest_network.h \
    Network/networkserver.h \
    Network/networkdatamanager.h
