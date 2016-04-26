######################################################################
#
######################################################################

TEMPLATE = app
TARGET = Heat_Conduction

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11
#CONFIG += console

INCLUDEPATH += src

include(src/src.pri)
include(test/test.pri)

DISTFILES += \
		README.md \
		LICENSE
