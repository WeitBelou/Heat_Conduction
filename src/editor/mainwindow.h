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

public slots:
	void compute();
	void setInputData(const QVector<Border> &value);

private slots:
	void setCurrentState(double percent);

private:
	void createCentralWidget();
	void createPlot();
	void createEditor();

	void createToolbar();
	void createActions();
	void createStatusBar();

	QProgressBar * currentState;

	QStatusBar * status;
	QToolBar * tools;

	QWidget * central;

	PlottingWidget * plot;
	Editor * editor;

	QAction * computeAct;

	QVector<Border> inputData;
};

#endif // MAINWINDOW_H
