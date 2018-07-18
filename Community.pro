#-------------------------------------------------
#
# Project created by QtCreator 2018-07-09T09:05:35
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Community
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
    logindialog.cpp \
    addpersondialog.cpp \
    findstaffdialog.cpp \
    leavedialog.cpp \
    agreevacdialog.cpp \
    addownerdialog.cpp \
    findownerdialog.cpp \
    addcardialog.cpp \
    findcardialog.cpp \
    applicatecardialog.cpp \
    rentcardialog.cpp \
    needrepairdialog.cpp \
    repairscheduledialog.cpp \
    aschredialog.cpp \
    ochredialog.cpp \
    attendstatedialog.cpp \
    helpdialog.cpp \
    setupdialog.cpp \
    chpassworddialog.cpp

HEADERS += \
        mainwindow.h \
    logindialog.h \
    addpersondialog.h \
    findstaffdialog.h \
    leavedialog.h \
    agreevacdialog.h \
    addownerdialog.h \
    findownerdialog.h \
    addcardialog.h \
    findcardialog.h \
    applicatecardialog.h \
    rentcardialog.h \
    needrepairdialog.h \
    repairscheduledialog.h \
    aschredialog.h \
    ochredialog.h \
    attendstatedialog.h \
    helpdialog.h \
    setupdialog.h \
    chpassworddialog.h

FORMS += \
        mainwindow.ui \
    logindialog.ui \
    addpersondialog.ui \
    findstaffdialog.ui \
    leavedialog.ui \
    agreevacdialog.ui \
    addownerdialog.ui \
    findownerdialog.ui \
    addcardialog.ui \
    findcardialog.ui \
    applicatecardialog.ui \
    rentcardialog.ui \
    needrepairdialog.ui \
    repairscheduledialog.ui \
    aschredialog.ui \
    ochredialog.ui \
    attendstatedialog.ui \
    helpdialog.ui \
    setupdialog.ui \
    chpassworddialog.ui

RESOURCES += \
    myimages.qrc \
    languages.qrc

RC_FILE = icon.rc

TRANSLATIONS += qzher_en.ts

