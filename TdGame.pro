#-------------------------------------------------
#
# Project created by QtCreator 2020-06-05T16:39:13
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TdGame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    object.cpp \
    enemy.cpp \
    mwfunction.cpp \
    mwdrawing.cpp \
    basetower.cpp \
    towerpos.cpp \
    bullet.cpp \
    selection.cpp \
    mypushbutton.cpp \
    chooselevelscene.cpp \
    playscene.cpp \
    tower1.cpp \
    flowerbullet.cpp \
    tower2.cpp \
    tower3.cpp

HEADERS += \
        mainwindow.h \
    point.h \
    object.h \
    enemy.h \
    basetower.h \
    towerpos.h \
    bullet.h \
    selection.h \
    mypushbutton.h \
    chooselevelscene.h \
    playscene.h \
    tower1.h \
    flowerbullet.h \
    tower2.h \
    tower3.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    media.qrc

