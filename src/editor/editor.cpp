#include "editor.h"
#include "calculatedialog.h"

Editor::Editor(QWidget *parent) : QWidget(parent)
{
	setWindowTitle("Editor");
	setMinimumSize(500, 500);

	main = new QVBoxLayout(this);

	err = new QErrorMessage(this);

	createActions();
	createMenu();
	createPlain();
}

Editor::~Editor()
{

}

void Editor::addPlot(PlottingWidget * plot)
{
	plots.push_back(plot);
}

void Editor::setCurrentFile(QString currentFile)
{
	if (m_currentFile == currentFile)
		return;

	m_currentFile = currentFile;
}

void Editor::newFile()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("New file"),
													"./untitled.txt",
													tr("Text files (*.txt)"));
	setCurrentFile(filename);
}

void Editor::parseText()
{
	try {
		inputData = MultiParse(plain->toPlainText());
	}
	catch (ParseError & p) {
		err->showMessage(QString("%1 \t %2").arg(p.where(), p.what()));
	}
}

void Editor::compute()
{
	if (inputData.isEmpty()) {
		return;
	}

	CalculateDialog * dl = new CalculateDialog(inputData, this);

	for (PlottingWidget * plot: plots) {
		connect(dl, &CalculateDialog::calculated, plot, &PlottingWidget::setData);
	}

	dl->exec();
}

void Editor::openFile()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),
												  "./", tr("Text files (*.txt)"));

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
													"./untitled.txt",
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
	parseMenu->addActions({parseAct, calculateAct});
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

	calculateAct = new QAction(tr("&Calculate"), this);
	calculateAct->setStatusTip(tr("Compute layers"));
	calculateAct->setShortcut(QString("F2"));
	connect(calculateAct, &QAction::triggered, this, &Editor::compute);

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
