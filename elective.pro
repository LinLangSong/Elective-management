#-------------------------------------------------
#
# Project created by QtCreator 2018-12-30T21:03:56
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = elective
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
    dialog1.cpp \
    dialog1_1.cpp \
    dialog2.cpp \
    dialog3.cpp \
    dialog3_1.cpp \
    dialog3_2.cpp \
    dialog3_3.cpp \
    dialog3_4.cpp \
    dialog3_5.cpp

HEADERS += \
        mainwindow.h \
    dialog1.h \
    dialog1_1.h \
    dialog2.h \
    dialog3.h \
    dialog3_1.h \
    dialog3_2.h \
    dialog3_3.h \
    dialog3_4.h \
    dialog3_5.h

FORMS += \
        mainwindow.ui \
    dialog1.ui \
    dialog1_1.ui \
    dialog2.ui \
    dialog3.ui \
    dialog3_1.ui \
    dialog3_2.ui \
    dialog3_3.ui \
    dialog3_4.ui \
    dialog3_5.ui

RESOURCES += \
    img.qrc
