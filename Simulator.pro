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
    reflector.cpp \
    diffractiongrating.cpp \
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
    opticaldevice.cpp \
    normal.cpp \
    pointsource.cpp \
    pointsourceform.cpp \
    opticalsystemwriter.cpp \
    opticalsystemreader.cpp \
    precisedoublespinbox.cpp \
    slit.cpp \
    slitform.cpp \
    zoomwidget.cpp \
    sizedialog.cpp \
    optionsdialog.cpp \
    simpleiconengine.cpp \
    orders.cpp

HEADERS  += mainwindow.h \
    planemirror.h \
    concavemirror.h \
    lightsource.h \
    reflector.h \
    diffractiongrating.h \
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
    opticaldevice.h \
    normal.h \
    pointsource.h \
    pointsourceform.h \
    opticalsystemwriter.h \
    opticalsystemreader.h \
    precisedoublespinbox.h \
    slit.h \
    slitform.h \
    zoomwidget.h \
    sizedialog.h \
    optionsdialog.h \
    simpleiconengine.h \
    orders.h
