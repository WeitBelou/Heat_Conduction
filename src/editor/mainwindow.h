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
	void setInputData(const QVector<Border> &value);

private slots:
	void addPlot();
	void addEditor();

private:
	void createCentralWidget();
	void createToolbar();
	void createActions();
	void createStatusBar();

	QLabel * currentState;

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
