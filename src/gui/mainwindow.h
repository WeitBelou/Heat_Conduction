#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "editor/editor.h"
#include "plot/plottingwidget.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);

private:
	void createCentralWidget();
	void createPlot();
	void createEditor();

	QStatusBar * status;
	QToolBar * tools;

	QMdiArea * central;

	PlottingWidget * plot;
	Editor * editor;
};

#endif // MAINWINDOW_H
