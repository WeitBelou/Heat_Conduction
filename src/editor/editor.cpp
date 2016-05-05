#include "editor.h"

#include "calculate_dialog.h"

#include "graphical_input/graphical_input_dialog.h"

#include "layer.h"
#include "tfdynamics.h"

Editor::Editor(QWidget *parent) : QWidget(parent)
{
	setWindowTitle("Editor");
	setMinimumSize(500, 500);

	main = new QVBoxLayout(this);

	err = new QErrorMessage(this);

	createActions();
	createMenus();
	createPlain();

	setCurrentFile("");
}

void Editor::closeEvent(QCloseEvent *event)
{
	if (maybeSave()) {
		event->accept();
	} else {
		event->ignore();
	}
}

void Editor::newFile()
{
	if (maybeSave()) {
		plain->clear();
		setCurrentFile("");
	}
}

void Editor::open()
{
	if (maybeSave()) {
		QString fileName = QFileDialog::getOpenFileName(this);
		if (!fileName.isEmpty()) {
			loadFile(fileName);
		}
	}
}

bool Editor::save()
{
	if (curFile.isEmpty()) {
		return saveAs();
	}
	else {
		return saveFile(curFile);
	}
}

bool Editor::saveAs()
{
	QFileDialog dialog(this);
	dialog.setWindowModality(Qt::WindowModal);
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	QStringList files;

	if (dialog.exec()) {
		files = dialog.selectedFiles();
	}
	else {
		return false;
	}

	return saveFile(files.at(0));
}

void Editor::about()
{
	QMessageBox::about(this, tr("About"), tr("Heat Conduction"));
}

void Editor::documentWasModified()
{
	setWindowModified(plain->document()->isModified());
}

void Editor::getGraphicalInput(const QVector<QVector<Border> > & figures)
{
	plain->clear();
	for (QVector<Border> figure: figures) {
		plain->appendPlainText("{");
		QString str;
		QTextStream s(&str);
		for (Border b: figure) {
			s << b << endl;
		}
		plain->appendPlainText(str.trimmed());
		plain->appendPlainText("}");
	}
}

void Editor::addPlot(PlottingWidget * plot)
{
	plots.push_back(plot);
}

void Editor::setCurrentFile(const QString & fileName)
{
	curFile = fileName;
	plain->document()->setModified(false);
	setWindowModified(false);

	QString shownName = curFile;
	if (curFile.isEmpty())
		shownName = "untitled.txt";
	setWindowFilePath(shownName);
}

QString Editor::strippedName(const QString & fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}


bool Editor::parse()
{
	try {
		inputData = MultiParse(plain->toPlainText());
		return true;
	}
	catch (ParseError & p) {
		err->showMessage(QString("%1 \t %2").arg(p.where(), p.what()));
		return false;
	}
}

void Editor::graphicalInput()
{
	newFile();
	GraphicalInputDialog * dialog = new GraphicalInputDialog(this);
	connect(dialog, &GraphicalInputDialog::parsed, this, &Editor::getGraphicalInput);
	dialog->exec();
	delete dialog;
}

void Editor::compute()
{
	if (!parse()) {
		return;
	}

	if (inputData.isEmpty()) {
		return;
	}

	CalculateDialog * dl = new CalculateDialog(inputData, this);

	for (PlottingWidget * plot: plots) {
		connect(dl, &CalculateDialog::calculated, plot, &PlottingWidget::setData);
	}

	dl->exec();
}

void Editor::createPlain()
{
	plain = new QPlainTextEdit(this);
	QFont font("Helvetica", 12, QFont::Bold);
	font.setStretch(QFont::SemiExpanded);
	font.setWordSpacing(4);
	plain->setFont(font);

	connect(plain, &QPlainTextEdit::textChanged,
			this, &Editor::documentWasModified);

	main->addWidget(plain);
}

void Editor::createMenus()
{
	menuBar = new QMenuBar(this);

	fileMenu = new QMenu("File", menuBar);
	fileMenu->addActions({newAct, openAct, saveAct,
						  saveAsAct, exitAct});
	menuBar->addMenu(fileMenu);

	menuBar->addSeparator();

	parseMenu = new QMenu("Compute", menuBar);
	parseMenu->addActions({graphicalInputAct, calculateAct});
	menuBar->addMenu(parseMenu);

	menuBar->addSeparator();

	helpMenu = new QMenu("Help", menuBar);
	helpMenu->addAction(aboutAct);
	menuBar->addMenu(helpMenu);

	main->addWidget(menuBar, 0, Qt::AlignTop);
}

void Editor::createActions()
{
	newAct = new QAction(tr("&New"), this);
	newAct->setStatusTip(tr("Create new file"));
	newAct->setShortcut(QKeySequence::New);
	connect(newAct, &QAction::triggered, this, &Editor::newFile);

	openAct = new QAction(tr("&Open"), this);
	openAct->setStatusTip(tr("Open existing file"));
	openAct->setShortcut(QKeySequence::Open);
	connect(openAct, &QAction::triggered, this, &Editor::open);

	saveAct = new QAction(tr("&Save"), this);
	saveAct->setStatusTip(tr("Save file"));
	saveAct->setShortcut(QKeySequence::Save);
	connect(saveAct, &QAction::triggered, this, &Editor::save);

	saveAsAct = new QAction(tr("&Save As..."), this);
	saveAsAct->setStatusTip(tr("Save file"));
	saveAsAct->setShortcut(QKeySequence::SaveAs);
	connect(saveAsAct, &QAction::triggered, this, &Editor::saveAs);

	calculateAct = new QAction(tr("&Calculate"), this);
	calculateAct->setStatusTip(tr("Compute layers"));
	calculateAct->setShortcut(QString("F2"));
	connect(calculateAct, &QAction::triggered, this, &Editor::compute);

	graphicalInputAct = new QAction(tr("&Grapical Input"), this);
	graphicalInputAct->setStatusTip(tr("Graphical Input"));
	connect(graphicalInputAct, &QAction::triggered, this, &Editor::graphicalInput);

	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setStatusTip(tr("About"));
	aboutAct->setShortcut(QKeySequence::HelpContents);
	connect(aboutAct, &QAction::triggered, this, &Editor::about);

	exitAct = new QAction(tr("&Close"), this);
	exitAct->setStatusTip(tr("Close file"));
	exitAct->setShortcut(QKeySequence::Quit);
	connect(exitAct, &QAction::triggered, parentWidget(), &QWidget::close);
}

bool Editor::maybeSave()
{
	if (plain->document()->isModified()) {
		QMessageBox::StandardButton ret;
		ret = QMessageBox::warning(this, tr("Heat Conduction"),
					 tr("The document has been modified.\n"
						"Do you want to save your changes?"),
					 QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		if (ret == QMessageBox::Save)
			return save();
		else if (ret == QMessageBox::Cancel)
			return false;
	}
	return true;
}

void Editor::loadFile(const QString & fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Heat Conduction"),
							 tr("Cannot read file %1:\n%2.")
							 .arg(fileName)
							 .arg(file.errorString()));
		return;
	}

	QTextStream in(&file);
#ifndef QT_NO_CURSOR
	QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
	plain->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif

	setCurrentFile(fileName);
	return;
}

bool Editor::saveFile(const QString & fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Heat Conduction"),
							 tr("Cannot write file %1:\n%2.")
							 .arg(fileName)
							 .arg(file.errorString()));
		return false;
	}

	QTextStream out(&file);
#ifndef QT_NO_CURSOR
	QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
	out << plain->toPlainText();
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif

	setCurrentFile(fileName);
	return true;
}
