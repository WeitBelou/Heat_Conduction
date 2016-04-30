#ifndef GRAPHICAL_INPUT_DIALOG_H
#define GRAPHICAL_INPUT_DIALOG_H

#include <QtWidgets>
#include "graphwidget.h"

class GraphicalInputDialog : public QDialog
{
	Q_OBJECT
public:
	explicit GraphicalInputDialog(QWidget * parent = 0);
private:
	GraphWidget * graph;
};

#endif // GRAPHICAL_INPUT_DIALOG_H
