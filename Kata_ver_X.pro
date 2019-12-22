#-------------------------------------------------
#
# Project created by QtCreator 2019-04-30T22:06:53
#
#-------------------------------------------------






QT       += core gui sql
QT += axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kata_ver_X
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

CONFIG += c++11

SOURCES += \
	data_dialog.cpp \
	dialogwithcategory.cpp \
	ended_competition.cpp \
        main.cpp \
		mainwindow.cpp \
	options.cpp \
    registration.cpp \
    fight.cpp \
    table.cpp \
    qdynamicsbutton.cpp

HEADERS += \
	data_dialog.h \
	dialogwithcategory.h \
	ended_competition.h \
        mainwindow.h \
	options.h \
    registration.h \
    fight.h \
    table.h \
    qdynamicsbutton.h

FORMS += \
	data_dialog.ui \
	dialogwithcategory.ui \
	ended_competition.ui \
        mainwindow.ui \
	options.ui \
    registration.ui \
    fight.ui \
    table.ui

win32:RC_ICONS +=main.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
