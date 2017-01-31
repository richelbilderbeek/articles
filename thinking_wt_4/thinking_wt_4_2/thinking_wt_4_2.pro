QT       += core
QT       -= gui

#Boost
LIBS += -lboost_signals

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
    thinking_wt_4_2.qrc
