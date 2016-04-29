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

MainWindow::~MainWindow()
{

}

void MainWindow::createPlot()
{
	plot = new PlottingWidget(this);
	editor->addPlot(plot);
	centralWidget()->layout()->addWidget(plot);
}

void MainWindow::createEditor()
{
	editor = new Editor(this);
	centralWidget()->layout()->addWidget(editor);
}

void MainWindow::createCentralWidget()
{
	central = new QWidget(this);
	central->setLayout(new QHBoxLayout(central));
	setCentralWidget(central);
}
