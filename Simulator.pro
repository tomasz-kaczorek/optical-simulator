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
    planemirrortab.cpp \
    concavemirror.cpp \
    concavemirrortab.cpp \
    lightsource.cpp \
    dockabletabwidget.cpp \
    reflector.cpp \
    diffractiongrating.cpp \
    diffractiongratingtab.cpp \
    lightsourcetab.cpp \
    reflectortab.cpp \
    aimdialog.cpp \
    ray.cpp \
    settings.cpp \
    absorber.cpp

HEADERS  += mainwindow.h \
    planemirror.h \
    planemirrortab.h \
    concavemirror.h \
    concavemirrortab.h \
    lightsource.h \
    dockabletabwidget.h \
    reflector.h \
    diffractiongrating.h \
    diffractiongratingtab.h \
    lightsourcetab.h \
    reflectortab.h \
    aimdialog.h \
    settings.h \
    ray.h \
    absorber.h
