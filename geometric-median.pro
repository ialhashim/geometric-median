QT       += core gui opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = geometric_median
TEMPLATE = app

INCLUDEPATH += .

SOURCES += main.cpp mainwindow.cpp Viewer.cpp
HEADERS += mainwindow.h  Viewer.h myglobals.h
FORMS   += mainwindow.ui Viewer.ui

HEADERS += geometric-median.h

OTHER_FILES += README.md
