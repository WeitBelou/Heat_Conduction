#include "mainwindow.h"
#include "../core/border_interpreter.h"

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
	if (inputData.isEmpty()) {
		return;
	}

	Border_interpreter borderInterpreter(inputData, 100);
	ArgumentForCalc arg = borderInterpreter.get_argument_for_calc();
	LayerCalc calculateAllLayers;
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
	plots.last()->show();
}

void MainWindow::addEditor()
{
	editors.append(new Editor(this));
	central->addSubWindow(editors.last());
	editors.last()->show();
	connect(editors.last(), &Editor::bordersParsed, this, &MainWindow::setInputData);
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
	connect(addPlotAct, &QAction::triggered, this, &MainWindow::addPlot);
}

void MainWindow::createStatusBar()
{
	status = new QStatusBar(this);
	setStatusBar(status);
}

void MainWindow::setInputData(const QVector<Border> &value)
{
	inputData = value;
}
