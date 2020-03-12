QT += testlib
QT += gui widgets
CONFIG += qt warn_on depend_includepath testcase
CONFIG += c++11

TEMPLATE = app

APP = $$PWD/../

include($${APP}/mcalendar.pri)

SOURCES +=  \
    tst_mcalendartest.cpp
