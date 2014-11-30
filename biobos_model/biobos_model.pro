#-------------------------------------------------
#
# Project created by QtCreator 2014-11-11T10:59:30
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = biobos_model
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    custommodel.cpp \
    DatabaseHandler/databasehandler.cpp \
    Model/basemodel.cpp \
    Model/bookingmodel.cpp \
    Model/hallmodel.cpp \
    Model/moviemodel.cpp \
    Model/seatmodel.cpp \
    Model/showmodel.cpp

HEADERS  += mainwindow.h \
    custommodel.h \
    DatabaseHandler/databasehandler.h \
    Model/basemodel.h \
    Model/bookingmodel.h \
    Model/hallmodel.h \
    Model/moviemodel.h \
    Model/seatmodel.h \
    Model/showmodel.h

FORMS    += mainwindow.ui
