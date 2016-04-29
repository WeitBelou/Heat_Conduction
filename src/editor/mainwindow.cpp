#include "mainwindow.h"
#include "../core/border_interpreter.h"
#include "calculatedialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	setWindowTitle("Heat Conduction");
	resize(1024, 600);

	createCentralWidget();

	createEditor();
	createPlot();

	setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::createPlot()
{
	plot = new PlottingWidget(this);
	editor->addPlot(plot);
	central->addSubWindow(plot);
}

void MainWindow::createEditor()
{
	editor = new Editor(this);
	central->addSubWindow(editor);
}

void MainWindow::createCentralWidget()
{
	central = new QMdiArea(this);
	central->setLayout(new QHBoxLayout(central));
	setCentralWidget(central);
}
