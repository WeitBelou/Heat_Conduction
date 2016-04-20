#include "editor.h"

Editor::Editor(QWidget *parent) : QWidget(parent)
{
	setWindowTitle("Editor");
	setMinimumSize(500, 500);

	main = new QVBoxLayout(this);

	createActions();
	createToolbar();
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

void Editor::createToolbar()
{
	tools = new QHBoxLayout();
	tools->addWidget(newAct);
	tools->addWidget(parseAct);
	tools->addWidget(openAct);
	tools->addWidget(saveAct);
	tools->addWidget(closeAct);
	main->addLayout(tools);
}

void Editor::createActions()
{
	newAct = new QPushButton(tr("&New"), this);
	newAct->setStatusTip(tr("Create new file"));
	newAct->setShortcut(QKeySequence::New);
	connect(newAct, &QPushButton::clicked, this, &Editor::newFile);

	parseAct = new QPushButton(tr("&Parse"), this);
	parseAct->setStatusTip(tr("Parse file to vector"));
	parseAct->setShortcut(QString("F5"));
	connect(parseAct, &QPushButton::clicked, this, &Editor::parseText);

	openAct = new QPushButton(tr("&Open"), this);
	openAct->setStatusTip(tr("Open existing file"));
	openAct->setShortcut(QKeySequence::Open);
	connect(openAct, &QPushButton::clicked, this, &Editor::openFile);

	saveAct = new QPushButton(tr("&Save"), this);
	saveAct->setStatusTip(tr("Save file"));
	saveAct->setShortcut(QKeySequence::Save);
	connect(saveAct, &QPushButton::clicked, this, &Editor::saveFile);

	closeAct = new QPushButton(tr("&Close"), this);
	closeAct->setStatusTip(tr("Close file"));
	closeAct->setShortcut(QKeySequence::Close);
	connect(closeAct, &QPushButton::clicked, this, &Editor::closeFile);
}
