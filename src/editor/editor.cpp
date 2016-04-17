#include "editor.h"

Editor::Editor(QWidget *parent) : QMainWindow(parent)
{
	setWindowTitle("Editor");
	resize(1024, 600);

	connect(this, &Editor::currentFileChanged, this, &Editor::fileChanged);

	createActions();
	createToolbar();
	createStatusBar();
	createCentralWidget();
	createPlain();
	createPlot();
}

Editor::~Editor()
{

}

void Editor::newFile()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("New file"),
													"/home/untitled.txt",
													tr("Text files (*.txt)"));
	setCurrentFile(filename);
}

void Editor::parseText()
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

void Editor::draw()
{
	plot->setData(outputData);
	plot->replot();
}

void Editor::openFile()
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

void Editor::saveFile()
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

void Editor::closeFile()
{
	close();
}

void Editor::createCentralWidget()
{
	central = new QMdiArea(this);
	central->tileSubWindows();
	setCentralWidget(central);
}

void Editor::createPlain()
{
	plain = new QPlainTextEdit(this);
	QFont font("Helvetica", 12, QFont::Bold);
	font.setStretch(QFont::SemiExpanded);
	font.setWordSpacing(4);
	plain->setFont(font);

	central->addSubWindow(plain);
}

void Editor::createPlot()
{
	plot = new PlottingWidget(this);
	central->addSubWindow(plot);
}

void Editor::createToolbar()
{
	tools = new QToolBar(this);
	tools->addActions({newAct, parseAct, drawAct, openAct, saveAct, closeAct});
	addToolBar(Qt::TopToolBarArea, tools);
}

void Editor::createActions()
{
	newAct = new QAction(tr("&New"), this);
	newAct->setStatusTip(tr("Create new file"));
	newAct->setShortcut(QKeySequence::New);
	connect(newAct, &QAction::triggered, this, &Editor::newFile);

	parseAct = new QAction(tr("&Parse"), this);
	parseAct->setStatusTip(tr("Parse file to vector"));
	parseAct->setShortcut(QString("F5"));
	connect(parseAct, &QAction::triggered, this, &Editor::parseText);

	drawAct = new QAction(tr("&Draw"), this);
	drawAct->setStatusTip(tr("Draw"));
	drawAct->setShortcut(QString("F9"));
	connect(drawAct, &QAction::triggered, this, &Editor::draw);

	openAct = new QAction(tr("&Open"), this);
	openAct->setStatusTip(tr("Open existing file"));
	openAct->setShortcut(QKeySequence::Open);
	connect(openAct, &QAction::triggered, this, &Editor::openFile);

	saveAct = new QAction(tr("&Save"), this);
	saveAct->setStatusTip(tr("Save file"));
	saveAct->setShortcut(QKeySequence::Save);
	connect(saveAct, &QAction::triggered, this, &Editor::saveFile);

	closeAct = new QAction(tr("&Close"), this);
	closeAct->setStatusTip(tr("Close file"));
	closeAct->setShortcut(QKeySequence::Close);
	connect(closeAct, &QAction::triggered, this, &Editor::closeFile);
}

void Editor::createStatusBar()
{
	status = new QStatusBar(this);
	currentState = new QLabel(m_currentFile, this);
	status->addWidget(currentState);
	setStatusBar(status);
}
