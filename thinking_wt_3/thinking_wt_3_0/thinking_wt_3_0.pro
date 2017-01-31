#-------------------------------------------------
#
# Project created by QtCreator 2010-09-17T11:09:34
#
#-------------------------------------------------
QT       += core
QT       -= gui
TARGET = CppThinkingWt3_0
LIBS += -L/usr/lib -lwt -lwthttp
QMAKE_CXXFLAGS += -DNDEBUG
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += \  
    main.cpp \
    tictactoe.cpp
HEADERS  += tictactoe.h
