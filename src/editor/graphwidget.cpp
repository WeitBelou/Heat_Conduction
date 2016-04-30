#include "graphwidget.h"
#include "edge.h"
#include "vertex.h"

#include <math.h>

#include <QKeyEvent>

GraphWidget::GraphWidget(QWidget *parent)
	: QGraphicsView(parent)
{
	createScene();
	currVertex = nullptr;
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
		Vertex * vertex = new Vertex(this);
		vertex->setPos(currPos);
		scene->addItem(vertex);
	}
}
