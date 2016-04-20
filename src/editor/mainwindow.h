#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "parser.h"
#include <QtWidgets>
#include "../core/layer.h"
#include "../draw/plottingwidget.h"
#include "../core/calc_func.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

signals:
	void currentFileChanged(QString currentFile);

public slots:
	void newFile();
	void parseText();
	void compute();
	void openFile();
	void saveFile();
	void closeFile();

	void fileChanged()
	{
		currentState->setText(m_currentFile);
	}

	void setCurrentFile(QString currentFile)
	{
		if (m_currentFile == currentFile)
			return;

		m_currentFile = currentFile;
		emit currentFileChanged(currentFile);
	}

private:
	void createCentralWidget();
	void createPlain();
	void createPlot();
	void createToolbar();
	void createActions();
	void createStatusBar();

	QString m_currentFile;
	QLabel * currentState;

	QStatusBar * status;
	QToolBar * tools;
	QMdiArea * central;
	QPlainTextEdit * plain;
	PlottingWidget * plot;

	QAction * newAct;
	QAction * parseAct;
	QAction * computeAct;
	QAction * openAct;
	QAction * saveAct;
	QAction * closeAct;

	QVector<Border> inputData;

	ArgumentForCalc gridData;
	ArgumentForDraw outputData;
};

#endif // MAINWINDOW_H
