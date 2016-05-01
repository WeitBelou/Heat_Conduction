#include "graphical_input_dialog.h"

GraphicalInputDialog::GraphicalInputDialog(QWidget * parent) :
	QDialog(parent)
{
	QVBoxLayout * main = new QVBoxLayout(this);
	graph = new GraphWidget(this);

	acceptButton = new QPushButton("OK", this);
	rejectButton = new QPushButton("Cancel", this);

	connect(acceptButton, &QPushButton::clicked, this, &GraphicalInputDialog::parse);
	connect(rejectButton, &QPushButton::clicked, this, &GraphicalInputDialog::cancel);


	main->addWidget(graph);
	main->addWidget(acceptButton);
	main->addWidget(rejectButton);

	connect(graph, &GraphWidget::figureCreated, this, &GraphicalInputDialog::addFigure);
}

void GraphicalInputDialog::addFigure(const QVector<Border> & figure)
{
	figures << figure;
}

void GraphicalInputDialog::parse()
{
	emit parsed(figures);
	accept();
}

void GraphicalInputDialog::cancel()
{
	reject();
}
