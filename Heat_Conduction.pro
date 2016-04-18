######################################################################
#
######################################################################

TEMPLATE = app
TARGET = Heat_Conduction

greaterThan(QT_MAJOR_VERSION, 4.7): QT += widgets

CONFIG += c++11
CONFIG += console

INCLUDEPATH += .

# Input
HEADERS += \
	src/core/border.h \
	src/core/calc_func.h \
	src/core/layer.h \
	src/draw/plottingwidget.h \
	src/editor/editor.h \
	src/editor/parser.h

SOURCES += \
	src/core/border.cpp \
	src/core/calc_func.cpp \
	src/draw/plottingwidget.cpp \
	src/editor/editor.cpp \
	src/editor/parser.cpp \
	src/main.cpp

DEFINES += QCUSTOMPLOT_USE_LIBRARY

CONFIG(debug, release|debug) {
  win32:QCPLIB = qcustomplotd1
  else: QCPLIB = qcustomplotd
} else {
  win32:QCPLIB = qcustomplot1
  else: QCPLIB = qcustomplot
}
LIBS += -L./ -l$$QCPLIB
