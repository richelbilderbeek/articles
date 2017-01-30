QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp

#Boost
LIBS += -lboost_signals

#Wt
LIBS += -lwt -lwthttp
