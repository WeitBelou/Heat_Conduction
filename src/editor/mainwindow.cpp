#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	setWindowTitle("Editor");
	resize(1024, 600);

	connect(this, &MainWindow::currentFileChanged, this, &MainWindow::fileChanged);

	createActions();
	createToolbar();
	createStatusBar();
	createCentralWidget();
	createPlain();
	createPlot();
}

MainWindow::~MainWindow()
{

}

void MainWindow::newFile()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("New file"),
													"/home/untitled.txt",
													tr("Text files (*.txt)"));
	setCurrentFile(filename);
}

void MainWindow::parseText()
{
	try {
		inputData = parsePlainText(plain->toPlainText());
	}
	catch (ParseError & p) {
		qWarning() << "On line: " << p.where();
		qWarning() << p.what();
		statusBar()->showMessage(p.what());
	}
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

void MainWindow::openFile()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),
												  "/home", tr("Text files (*.txt)"));

	QFile file(filename);

	if (!file.open(QIODevice::ReadOnly)) {
		return;
	}
	QTextStream tstream(&file);

	plain->setPlainText(tstream.readAll());

	file.close();

	setCurrentFile(filename);
}

void MainWindow::saveFile()
{
	if (m_currentFile.isNull()) {
		setCurrentFile(QFileDialog::getSaveFileName(this, tr("New file"),
													"/home/untitled.txt",
													tr("Text files (*.txt)")));
	}

	QFile file(m_currentFile);

	if (!file.open(QIODevice::WriteOnly)) {
		return;
	}
	QTextStream tstream(&file);

	tstream << plain->toPlainText();

	file.close();
}

void MainWindow::closeFile()
{
	close();
}

void MainWindow::createCentralWidget()
{
	central = new QMdiArea(this);
	central->tileSubWindows();
	setCentralWidget(central);
}

void MainWindow::createPlain()
{
	plain = new QPlainTextEdit(this);
	QFont font("Helvetica", 12, QFont::Bold);
	font.setStretch(QFont::SemiExpanded);
	font.setWordSpacing(4);
	plain->setFont(font);

	central->addSubWindow(plain);
}

void MainWindow::createPlot()
{
	plot = new PlottingWidget(this);
	central->addSubWindow(plot);
}

void MainWindow::createToolbar()
{
	tools = new QToolBar(this);
	tools->addActions({newAct, parseAct, computeAct,
					   openAct, saveAct, closeAct});
	addToolBar(Qt::TopToolBarArea, tools);
}

void MainWindow::createActions()
{
	newAct = new QAction(tr("&New"), this);
	newAct->setStatusTip(tr("Create new file"));
	newAct->setShortcut(QKeySequence::New);
	connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

	parseAct = new QAction(tr("&Parse"), this);
	parseAct->setStatusTip(tr("Parse file to vector"));
	parseAct->setShortcut(QString("F5"));
	connect(parseAct, &QAction::triggered, this, &MainWindow::parseText);

	computeAct = new QAction(tr("&Compute"), this);
	computeAct->setStatusTip(tr("Compute layers"));
	computeAct->setShortcut(QString("F6"));
	connect(computeAct, &QAction::triggered, this, &MainWindow::compute);

	openAct = new QAction(tr("&Open"), this);
	openAct->setStatusTip(tr("Open existing file"));
	openAct->setShortcut(QKeySequence::Open);
	connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

	saveAct = new QAction(tr("&Save"), this);
	saveAct->setStatusTip(tr("Save file"));
	saveAct->setShortcut(QKeySequence::Save);
	connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

	closeAct = new QAction(tr("&Close"), this);
	closeAct->setStatusTip(tr("Close file"));
	closeAct->setShortcut(QKeySequence::Close);
	connect(closeAct, &QAction::triggered, this, &MainWindow::closeFile);
}

void MainWindow::createStatusBar()
{
	status = new QStatusBar(this);
	currentState = new QLabel(m_currentFile, this);
	status->addWidget(currentState);
	setStatusBar(status);
}
