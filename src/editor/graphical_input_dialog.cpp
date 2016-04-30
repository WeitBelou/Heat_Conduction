#include "graphical_input_dialog.h"

GraphicalInputDialog::GraphicalInputDialog(QWidget * parent) :
	QDialog(parent)
{
	QVBoxLayout * main = new QVBoxLayout(this);
	graph = new GraphWidget(this);
	main->addWidget(graph);
}

