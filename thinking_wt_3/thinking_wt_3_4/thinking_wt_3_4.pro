#-------------------------------------------------
#
# Project created by QtCreator 2010-09-17T11:09:34
#
#-------------------------------------------------
QT       += core
QT       -= gui
TARGET = CppThinkingWt3_4
LIBS +=  -lwt -lwthttp
QMAKE_CXXFLAGS += -DNDEBUG
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += \  
    main.cpp \
    tictactoe.cpp
HEADERS  += tictactoe.h
