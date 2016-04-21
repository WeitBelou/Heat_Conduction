#ifndef EDITOR_H
#define EDITOR_H

#include "parser.h"
#include <QtWidgets>
#include "../core/layer.h"
#include "../core/argument.h"

class Editor : public QWidget
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
	void openFile();
	void saveFile();
	void closeFile();

	void setCurrentFile(QString currentFile)
	{
		if (m_currentFile == currentFile)
			return;

		m_currentFile = currentFile;
	}

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
	QAction * openAct;
	QAction * saveAct;
	QAction * closeAct;

	QVector<Border> inputData;
};

#endif // EDITOR_H
