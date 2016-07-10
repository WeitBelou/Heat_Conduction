#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

#include "plot/plottingwidget.h"

#include "editor/editor.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);

private:
	void createCentralWidget();
	void createPlot();
	void createEditor();

	QMdiArea * central;

	PlottingWidget * plot;
	Editor * editor;
};

#endif // MAINWINDOW_H
