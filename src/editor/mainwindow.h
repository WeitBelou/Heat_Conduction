#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "parser.h"
#include <QtWidgets>
#include "../core/layer.h"
#include "../editor/editor.h"
#include "../draw/plottingwidget.h"
#include "../core/tfgeometry.h"
#include "../core/tfdynamics.h"
#include "../core/problem.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	void createCentralWidget();
	void createPlot();
	void createEditor();

	QStatusBar * status;
	QToolBar * tools;

	QWidget * central;

	PlottingWidget * plot;
	Editor * editor;
};

#endif // MAINWINDOW_H
