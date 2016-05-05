######################################################################
#
######################################################################

TEMPLATE = app
TARGET = Heat_Conduction

DESTDIR = $$PWD/bin

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11
CONFIG -= console

INCLUDEPATH += src src/components

include(src/src.pri)
include(test/test.pri)
include(bin/bin.pri)

QMAKE_CXXFLAGS_DEBUG += -O0
QMAKE_CXXFLAGS_RELEASE += -O3

QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp

DISTFILES += \
		README.md \
		LICENSE
