QT += core widgets
CONFIG += c++11

INCLUDEPATH += $$PWD

HEADERS += $$PWD/mcalendar.h \
    $$PWD/sampleday.h

SOURCES += $$PWD/mcalendar.cpp \
    $$PWD/sampleday.cpp

DEFINES += MCALENDAR_LIB