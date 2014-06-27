#-------------------------------------------------
#
# Project created by QtCreator 2013-11-05T17:35:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Simulator
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
    mainwindow.cpp \
    planemirror.cpp \
    concavemirror.cpp \
    lightsource.cpp \
    dockabletabwidget.cpp \
    reflector.cpp \
    diffractiongrating.cpp \
    reflectortab.cpp \
    aimdialog.cpp \
    ray.cpp \
    settings.cpp \
    absorber.cpp \
    opticalsystem.cpp \
    label.cpp \
    opticaldeviceform.cpp \
    planemirrorform.cpp \
    opticaldevicetabwidget.cpp \
    concavemirrorform.cpp \
    diffractiongratingform.cpp \
    lightsourceform.cpp \
    opticaldevice.cpp

HEADERS  += mainwindow.h \
    planemirror.h \
    concavemirror.h \
    lightsource.h \
    dockabletabwidget.h \
    reflector.h \
    diffractiongrating.h \
    reflectortab.h \
    aimdialog.h \
    settings.h \
    ray.h \
    absorber.h \
    opticalsystem.h \
    label.h \
    opticaldeviceform.h \
    planemirrorform.h \
    opticaldevicetabwidget.h \
    concavemirrorform.h \
    diffractiongratingform.h \
    lightsourceform.h \
    opticaldevice.h
