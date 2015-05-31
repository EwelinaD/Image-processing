#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T21:00:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PrzetwarzanieObrazow
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageview.cpp \
    optionsview.cpp \
    kirschfilter.cpp \
    imopen.cpp \
    geodistance.cpp \
    nearest.cpp

HEADERS  += mainwindow.h \
    imageview.h \
    optionsview.h \
    kirschfilter.h \
    imopen.h \
    geodistance.h \
    nearest.h

FORMS    += mainwindow.ui \
    imageview.ui \
    optionsview.ui
