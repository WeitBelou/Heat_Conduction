#include "mainwindow.h"
#include "../core/border_interpreter.h"
#include "calculatedialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	setWindowTitle("Heat Conduction");
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

	CalculateDialog * dl = new CalculateDialog(inputData, this);

	connect(dl, &CalculateDialog::calculated, plot, &PlottingWidget::setData);

	if (dl->exec() == QDialog::Accepted) {
		qDebug() << "MALADCA" << endl;
	}
	else {
		qDebug() << "SASAI LALKA" << endl;
	}
}

void MainWindow::setInputData(const QVector<QVector<Border> > & borders)
{
	inputData = borders;
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
