QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

#Boost
LIBS += -lboost_signals -lboost_filesystem -lboost_system

#Wt
LIBS += -lwt -lwthttp
#Wt uses Boost.Signal, which is deprecated
DEFINES += BOOST_SIGNALS_NO_DEPRECATION_WARNING

SOURCES += main.cpp \
    tictactoe.cpp
HEADERS  += tictactoe.h

OTHER_FILES += \
    wt.css

RESOURCES += \
    thinking_wt_4_1.qrc
