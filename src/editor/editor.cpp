#include "editor.h"

Editor::Editor(QWidget *parent) : QWidget(parent)
{
	setWindowTitle("Editor");
	setMinimumSize(500, 500);

	main = new QVBoxLayout(this);

	createActions();
	createMenu();
	createPlain();
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
	}
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

void Editor::createPlain()
{
	plain = new QPlainTextEdit(this);
	QFont font("Helvetica", 12, QFont::Bold);
	font.setStretch(QFont::SemiExpanded);
	font.setWordSpacing(4);
	plain->setFont(font);
	main->addWidget(plain);
}

void Editor::createMenu()
{
	menuBar = new QMenuBar(this);

	fileMenu = new QMenu("File", menuBar);
	fileMenu->addActions({newAct, openAct,saveAct, closeAct});
	menuBar->addMenu(fileMenu);

	menuBar->addSeparator();

	parseMenu = new QMenu("Parse", menuBar);
	parseMenu->addActions({parseAct});
	menuBar->addMenu(parseMenu);

	main->addWidget(menuBar, 0, Qt::AlignTop);
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
