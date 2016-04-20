#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "parser.h"
#include <QtWidgets>
#include "../core/layer.h"
#include "../editor/editor.h"
#include "../draw/plottingwidget.h"
#include "../core/calc_func.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

signals:
	void currentFileChanged(QString currentFile);

public slots:
	void compute();

private:
	void createCentralWidget();
	void createEditor();
	void createPlot();
	void createToolbar();
	void createActions();
	void createStatusBar();

	QLabel * currentState;

	QStatusBar * status;
	QToolBar * tools;
	QMdiArea * central;
	Editor * editor;
	PlottingWidget * plot;

	QAction * computeAct;

	QVector<Border> inputData;

	ArgumentForCalc gridData;
	ArgumentForDraw outputData;
};

#endif // MAINWINDOW_H
