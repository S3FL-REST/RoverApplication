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
    Network/networkdatamanager.cpp \
    Computer/temperaturemonitor.cpp \
    Vision/camera.cpp \
    Vision/robotvision.cpp \
    Controls/robotcollection.cpp

HEADERS += \
    Serial/serialport.h \
    robotmain.h \
    Serial/serialmanager.h \
    Controls/robotdrive.h \
    Protocols/rest_network.h \
    Network/networkserver.h \
    Network/networkdatamanager.h \
    Computer/temperaturemonitor.h \
    Vision/camera.h \
    Vision/robotvision.h \
    Controls/robotcollection.h

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}
