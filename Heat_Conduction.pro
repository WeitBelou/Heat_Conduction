######################################################################
#
######################################################################

TEMPLATE = app
TARGET = Heat_Conduction

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11
CONFIG -= console

INCLUDEPATH += src src/components

DESTDIR = $$PWD/bin

QMAKE_LFLAGS += -fopenmp
QMAKE_CXXFLAGS += -fopenmp

include(src/src.pri)
include(test/test.pri)
include(bin/bin.pri)

DISTFILES += \
		README.md \
		LICENSE
