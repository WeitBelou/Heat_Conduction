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
	src/core/calc_func.h \
	src/core/layer.h \
	src/draw/qcustomplot.h \
	src/draw/plottingwidget.h \
	src/editor/editor.h \
	src/editor/parser.h \
	src/core/argument.h \

SOURCES += \
	src/core/border.cpp \
	src/core/calc_func.cpp \
	src/draw/qcustomplot.cpp \
	src/draw/plottingwidget.cpp \
	src/editor/editor.cpp \
	src/editor/parser.cpp \
	src/main.cpp \
	src/core/argument.cpp \


