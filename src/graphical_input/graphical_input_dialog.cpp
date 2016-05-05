#include "graphical_input_dialog.h"
#include "vertex.h"
#include "edge.h"

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
}

void GraphicalInputDialog::addFigure(const QVector<Border> & figure)
{
	figures << figure;
}

void GraphicalInputDialog::parse()
{
	QVector<QVector<Vertex *> > allFigures = graph->getAllFigures();

	for (QVector<Vertex *> figure: allFigures) {
		QVector<Border> borders;
		for (Vertex * vertex: figure) {
			Edge * edge = vertex->firstEdge();
			borders << edge->toBorder();
		}
		figures << borders;
	}

	emit parsed(figures);
	accept();
}

void GraphicalInputDialog::cancel()
{
	reject();
}
