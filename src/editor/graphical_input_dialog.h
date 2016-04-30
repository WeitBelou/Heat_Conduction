#ifndef GRAPHICAL_INPUT_DIALOG_H
#define GRAPHICAL_INPUT_DIALOG_H

#include <QtWidgets>
#include "graphwidget.h"

class GraphicalInputDialog : public QDialog
{
	Q_OBJECT
public:
	explicit GraphicalInputDialog(QWidget * parent = 0);

signals:
	void parsed(const QVector<QVector<Border> > & figures);

private slots:
	void addFigure(const QVector<Border> & figure);
	void parse();
	void cancel();

private:
	GraphWidget * graph;

	QPushButton * acceptButton;
	QPushButton * rejectButton;

	QVector<QVector<Border> > figures;
};

#endif // GRAPHICAL_INPUT_DIALOG_H
