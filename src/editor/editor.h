#ifndef EDITOR_H
#define EDITOR_H

#include "parser.h"
#include "plot/plottingwidget.h"

class Editor : public QWidget
{
	Q_OBJECT
public:
	explicit Editor(QWidget *parent = 0);

protected:
	void closeEvent(QCloseEvent * event) override;

public slots:
	void addPlot(PlottingWidget * plot);

signals:
	void bordersParsed(const QVector<QVector<Border> > & borders);

private slots:
	void newFile();
	bool parse();
	void graphicalInput();
	void compute();
	void open();
	bool save();
	bool saveAs();
	void about();
	void documentWasModified();
	void getGraphicalInput(const QVector<QVector<Border> > & figures);


private:
	void createPlain();
	void createMenus();
	void createActions();
	bool maybeSave();

	void loadFile(const QString & fileName);
	bool saveFile(const QString & fileName);
	void setCurrentFile(const QString & fileName);

	QString strippedName(const QString & fullFileName);

	QString curFile;

	QVBoxLayout * main;
	QPlainTextEdit * plain;

	QMenuBar * menuBar;
	QMenu * fileMenu;
	QMenu * parseMenu;
	QMenu * helpMenu;

	QAction * newAct;
	QAction * openAct;
	QAction * saveAct;
	QAction * saveAsAct;
	QAction * aboutAct;
	QAction * exitAct;

	QAction * graphicalInputAct;
	QAction * calculateAct;

	QErrorMessage * err;

	QVector<QVector<Border> > inputData;

	QList<PlottingWidget *> plots;
};

#endif // EDITOR_H
