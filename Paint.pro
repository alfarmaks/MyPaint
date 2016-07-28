#-------------------------------------------------
#
# Project created by QtCreator 2016-07-23T16:47:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Paint
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    about.cpp \
    scene.cpp

HEADERS  += mainwindow.h \
    about.h \
    scene.h

FORMS    += mainwindow.ui \
    about.ui

RESOURCES += \
    path.qrc
