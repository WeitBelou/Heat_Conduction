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

	createEditor();
	createPlot();
}

MainWindow::~MainWindow()
{

}

void MainWindow::compute()
{
	if (inputData.isEmpty()) {
		return;
	}

	BorderInterpreter borderInterpreter(inputData, 100);
	TFGeometry geom = borderInterpreter.workingArea();

	QFile logg("./loggg.txt");
	logg.open(QIODevice::WriteOnly);
	QTextStream str(&logg);
	str << geom.idNet() << endl;
	logg.close();

	Material m;

	double tMax = QInputDialog::getDouble(this, tr("Input max time"),
								   tr("Max time"), 100, 0, 100000);

	double tStep = QInputDialog::getDouble(this, tr("Input time step"),
								   tr("Time step"), 1, 0, 100);

	Problem * p =  new Problem(m, geom, tMax, tStep, this);

	QProgressDialog * progress = new QProgressDialog("Calculate", "Cancel", 0, 98, this);
	progress->setMinimumDuration(0);

	connect(p, &Problem::oneLayerCalcSignal, [progress](double percent){
		qApp->processEvents();
		progress->setValue(100 * percent);
	});

	TFDynamics dyn = p->solve();

	delete p;
	delete progress;

	plot->setData(dyn);
}

void MainWindow::createPlot()
{
	plot = new PlottingWidget(this);
	centralWidget()->layout()->addWidget(plot);
}

void MainWindow::createEditor()
{
	editor = new Editor(this);
	centralWidget()->layout()->addWidget(editor);
	connect(editor, &Editor::bordersParsed, this, &MainWindow::setInputData);
}

void MainWindow::createCentralWidget()
{
	central = new QWidget(this);
	central->setLayout(new QHBoxLayout(central));
	setCentralWidget(central);
}

void MainWindow::createToolbar()
{
	tools = new QToolBar(this);
	tools->addActions({computeAct});
	addToolBar(Qt::TopToolBarArea, tools);
}

void MainWindow::createActions()
{
	computeAct = new QAction(tr("&Compute"), this);
	computeAct->setStatusTip(tr("Compute layers"));
	computeAct->setShortcut(QString("F2"));
	connect(computeAct, &QAction::triggered, this, &MainWindow::compute);
}

void MainWindow::createStatusBar()
{
	status = new QStatusBar(this);
	setStatusBar(status);
}

void MainWindow::setInputData(const QVector<QVector<Border> > &value)
{
	inputData.clear();

	for (QVector<Border> b: value) {
		for (Border bor: b) {
			inputData.push_back(bor);
		}
	}
}
