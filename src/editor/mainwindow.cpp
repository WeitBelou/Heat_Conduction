#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	setWindowTitle("Editor");
	resize(1024, 600);

	createActions();
	createToolbar();
	createStatusBar();
	createCentralWidget();
	addEditor();
	addPlot();
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

	for (PlottingWidget * plot: plots)
	{
		plot->setData(outputData);
	}
}

void MainWindow::addPlot()
{
	plots.append(new PlottingWidget(this));
	central->addSubWindow(plots.last());
}

void MainWindow::addEditor()
{
	editors.append(new Editor(this));
	central->addSubWindow(editors.last());
	editors.last()->show();
}

void MainWindow::createCentralWidget()
{
	central = new QMdiArea(this);
	central->tileSubWindows();
	setCentralWidget(central);
}

void MainWindow::createToolbar()
{
	tools = new QToolBar(this);
	tools->addActions({addEditorAct, addPlotAct, computeAct});
	addToolBar(Qt::TopToolBarArea, tools);
}

void MainWindow::createActions()
{
	computeAct = new QAction(tr("&Compute"), this);
	computeAct->setStatusTip(tr("Compute layers"));
	computeAct->setShortcut(QString("F2"));
	connect(computeAct, &QAction::triggered, this, &MainWindow::compute);

	addEditorAct = new QAction(tr("&Add Editor"), this);
	addEditorAct->setStatusTip(tr("Add Editor"));
	addEditorAct->setShortcut(QString("F3"));
	connect(addEditorAct, &QAction::triggered, this, &MainWindow::addEditor);

	addPlotAct = new QAction(tr("&Add Plot"), this);
	addPlotAct->setStatusTip(tr("Add Plot"));
	addPlotAct->setShortcut(QString("F4"));
	connect(addPlotAct, &QAction::triggered, this, &MainWindow::addEditor);
}

void MainWindow::createStatusBar()
{
	status = new QStatusBar(this);
	setStatusBar(status);
}
