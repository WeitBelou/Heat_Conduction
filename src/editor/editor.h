#ifndef EDITOR_H
#define EDITOR_H

#include "parser.h"
#include <QtWidgets>
#include "draw/plottingwidget.h"
#include "core/layer.h"
#include "core/tfdynamics.h"

class Editor : public QWidget
{
	Q_OBJECT
public:
	explicit Editor(QWidget *parent = 0);
	~Editor();

signals:
	void currentFileChanged(QString currentFile);

public slots:
	void addPlot(PlottingWidget * plot);

signals:
	void bordersParsed(const QVector<QVector<Border> > & borders);

private slots:
	void newFile();
	void parseText();
	void compute();
	void openFile();
	void saveFile();
	void closeFile();

	void setCurrentFile(QString currentFile);

private:
	void createPlain();
	void createMenu();
	void createActions();

	QString m_currentFile;

	QVBoxLayout * main;
	QPlainTextEdit * plain;

	QMenuBar * menuBar;
	QMenu * fileMenu;
	QMenu * parseMenu;

	QAction * newAct;
	QAction * parseAct;
	QAction * calculateAct;
	QAction * openAct;
	QAction * saveAct;
	QAction * closeAct;

	QErrorMessage * err;

	QVector<QVector<Border> > inputData;

	QList<PlottingWidget *> plots;
};

#endif // EDITOR_H
