QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

#Boost
LIBS += -lboost_signals

#Wt
LIBS += -lwt -lwthttp

SOURCES += \  
    main.cpp \
    tictactoe.cpp
HEADERS  += tictactoe.h
