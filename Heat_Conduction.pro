######################################################################
#
######################################################################

TEMPLATE = app
TARGET = Heat_Conduction

greaterThan(QT_MAJOR_VERSION, 4.7): QT += widgets printsupport

CONFIG += c++11
CONFIG += console
CONFIG += silent

INCLUDEPATH += src

include(src/src.pri)
include(test/test.pri)
