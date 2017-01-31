QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

#Boost
LIBS += -lboost_signals

#Wt
LIBS += -lwt -lwthttp
#Wt uses Boost.Signal, which is deprecated
DEFINES += BOOST_SIGNALS_NO_DEPRECATION_WARNING

SOURCES += \  
    main.cpp \
    tictactoe.cpp
HEADERS  += tictactoe.h
