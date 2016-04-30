#include "graphwidget.h"
#include "edge.h"
#include "vertex.h"
#include <QDebug>

#include <math.h>

#include <QKeyEvent>

GraphWidget::GraphWidget(QWidget *parent)
	: QGraphicsView(parent)
{
	createScene();
	firstVertex = currVertex = nullptr;
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
	Q_UNUSED(rect);

	QRectF sceneRect = this->sceneRect();

	drawGrid(painter, sceneRect);

	painter->setBrush(Qt::NoBrush);
	painter->drawRect(sceneRect);
}

void GraphWidget::createScene()
{
	scene = new QGraphicsScene(this);
	scene->setSceneRect(-200, -200, 400, 400);
	setScene(scene);
	setCacheMode(CacheBackground);
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(AnchorUnderMouse);
	setMinimumSize(400, 400);
}

void GraphWidget::drawGrid(QPainter * painter, const QRectF & rect)
{
	double xMin = rect.left();
	double xMax = rect.right();
	double yMin = rect.top();
	double yMax = rect.bottom();

	double xStep = rect.width() / 5;
	double yStep = rect.height() / 5;

	QPen majorGridPen;
	majorGridPen.setColor(Qt::blue);
	majorGridPen.setWidth(0);

	painter->setPen(majorGridPen);

	//Vertical major grid lines
	for (double x = xMin; x < xMax; x += xStep) {
		painter->drawLine(x, yMin, x, yMax);
	}

	//Horizontal major grid lines
	for (double y = yMin; y < yMax; y += yStep) {
		painter->drawLine(xMin, y, xMax, y);
	}
}


void GraphWidget::mousePressEvent(QMouseEvent * mouse)
{
	QPointF currPos = this->mapToScene(mouse->pos());

	if (!currVertex) {
		currFigure.clear();
		Vertex * vertex = new Vertex(this);
		vertex->setPos(currPos);
		scene->addItem(vertex);
		firstVertex = currVertex = vertex;
	}
	else {
		QGraphicsItem * onScene = scene->itemAt(currPos, transform());
		if (onScene && onScene->type() == Vertex::Type && onScene == firstVertex) {
			Edge * edge = new Edge(currVertex, firstVertex);
			scene->addItem(edge);

			double u = QInputDialog::getDouble(this, tr("Input temperature"),
											   tr("Input temperature"),
											   100, 0);

			Border b(Point(currPos.x(), currPos.y()),
					 Point(firstVertex->x(), firstVertex->y()), u);
			currFigure << b;

			emit figureCreated(currFigure);
			firstVertex = currVertex = nullptr;
			return;
		}
		Vertex * vertex = new Vertex(this);
		vertex->setPos(currPos);
		Edge * edge = new Edge(currVertex, vertex);

		scene->addItem(vertex);
		scene->addItem(edge);

		double u = QInputDialog::getDouble(this, tr("Input temperature"),
										   tr("Input temperature"),
										   100, 0);
		Border b(Point(currPos.x(), currPos.y()),
				 Point(vertex->x(), vertex->y()), u);
		currFigure.push_back(b);

		currVertex = vertex;
	}
}
