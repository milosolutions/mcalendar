TEMPLATE = app
include(../mcalendar.pri)

QT -= gui


TARGET = mcalendar
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle


SOURCES += main.cpp

