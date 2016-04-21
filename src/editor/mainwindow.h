#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "parser.h"
#include <QtWidgets>
#include "../core/layer.h"
#include "../editor/editor.h"
#include "../draw/plottingwidget.h"
#include "../core/layercalc.h"

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
	void addPlot();
	void addEditor();
	void setCurrentState(double percent);

private:
	void createCentralWidget();
	void createToolbar();
	void createActions();
	void createStatusBar();

	QProgressBar * currentState;

	QStatusBar * status;
	QToolBar * tools;
	QMdiArea * central;

	QList<Editor *> editors;
	QList<PlottingWidget *> plots;

	QAction * addEditorAct;
	QAction * addPlotAct;
	QAction * computeAct;

	QVector<Border> inputData;
	ArgumentForCalc gridData;
	ArgumentForDraw outputData;
};

#endif // MAINWINDOW_H
