######################################################################
#
######################################################################

TEMPLATE = app
TARGET = Heat_Conduction

greaterThan(QT_MAJOR_VERSION, 4.7): QT += widgets printsupport

CONFIG += c++11
CONFIG += console

INCLUDEPATH += .

# Input
HEADERS += \
	src/core/border.h \
	src/core/layer.h \
	src/draw/qcustomplot.h \
	src/draw/plottingwidget.h \
	src/editor/editor.h \
	src/editor/parser.h \
    src/core/border_interpreter.h \
    src/editor/mainwindow.h \
    src/core/material.h \
    src/core/tfgeometry.h \
    src/core/point.h \
    src/core/tfdynamics.h \
    src/core/problem.h

SOURCES += \
	src/core/border.cpp \
	src/draw/qcustomplot.cpp \
	src/draw/plottingwidget.cpp \
	src/editor/editor.cpp \
	src/editor/parser.cpp \
	src/main.cpp \
    src/core/border_interpreter.cpp \
    src/editor/mainwindow.cpp \
    src/core/material.cpp \
    src/core/tfgeometry.cpp \
    src/core/tfdynamics.cpp \
    src/core/problem.cpp


