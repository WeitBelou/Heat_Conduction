#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	setWindowTitle("Editor");
	resize(1024, 600);

	createActions();
	createToolbar();
	createStatusBar();
	createCentralWidget();
	createEditor();
	createPlot();
}

MainWindow::~MainWindow()
{

}

void MainWindow::compute()
{
	//Сформируем данные
	int N = 100;
	Layer L(N, N);
	BoolNet B(N, N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if ((10 < i && i < 90) && (10 < j && j < 90)){
				L(i, j) = 5;
				B(i, j) = true;
			}
			else {
				if ((10 <= j && j <= 90) && (i == 10 || i == 90)) {
					L(i, j) = 10;
					B(i, j) = false;
				}
				else if ((10 <= i && i <= 90) && (j == 10 || j == 90)) {
					L(i, j) = 20;
					B(i, j) = false;
				}
				else {
					L(i, j) = 0;
					B(i, j) = false;
				}
			}
		}
	}
	ArgumentForCalc arg(L, B, 100, 1, 0.01, 0.01, 7800, 46, 460);
	outputData = calculateAllLayers(arg);

	plot->setData(outputData);
}

void MainWindow::createCentralWidget()
{
	central = new QMdiArea(this);
	central->tileSubWindows();
	setCentralWidget(central);
}

void MainWindow::createEditor()
{
	editor = new Editor(this);
	central->addSubWindow(editor);
}

void MainWindow::createPlot()
{
	plot = new PlottingWidget(this);
	central->addSubWindow(plot);
}

void MainWindow::createToolbar()
{
	tools = new QToolBar(this);
	tools->addAction(computeAct);
	addToolBar(Qt::TopToolBarArea, tools);
}

void MainWindow::createActions()
{
	computeAct = new QAction(tr("&Compute"), this);
	computeAct->setStatusTip(tr("Compute layers"));
	computeAct->setShortcut(QString("F6"));
	connect(computeAct, &QAction::triggered, this, &MainWindow::compute);
}

void MainWindow::createStatusBar()
{
	status = new QStatusBar(this);
	setStatusBar(status);
}
