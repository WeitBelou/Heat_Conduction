#ifndef EDITOR_H
#define EDITOR_H

#include "parser.h"
#include <QtWidgets>
#include "../core/layer.h"
#include "../draw/plottingwidget.h"
#include "../core/calc_func.h"

class Editor : public QMainWindow
{
	Q_OBJECT
public:
	explicit Editor(QWidget *parent = 0);
	~Editor();

signals:
	void currentFileChanged(QString currentFile);

public slots:
	void newFile();
	void parseText();
	void draw();
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
	QAction * drawAct;
	QAction * openAct;
	QAction * saveAct;
	QAction * closeAct;

	QVector<Border> inputData;

	QVector<Layer> outputData;
};

#endif // EDITOR_H
