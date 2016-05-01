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
	createGrid();
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
	double a = QInputDialog::getDouble(this, "Input width", "Width", 10, 1, 1000);
	double h = QInputDialog::getDouble(this, "Input height", "Height", 10, 1, 1000);
	scene = new QGraphicsScene(this);
	scene->setSceneRect(0, 0, a, h);
	setScene(scene);

	scale(400 / a, 400 / h);
	scale(1, -1);
	setCacheMode(CacheBackground);
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(AnchorUnderMouse);
}

void GraphWidget::createGrid()
{
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

QVector<QVector<Vertex *> > GraphWidget::getAllFigures() const
{
	return allFigures;
}


void GraphWidget::mousePressEvent(QMouseEvent * mouse)
{
	QPointF currPos = this->mapToScene(mouse->pos());

	if (currFigure.isEmpty()) {
		beginFigure(currPos);
	}
	else {
		QGraphicsItem * onScene = scene->itemAt(currPos, transform());
		if (onScene){
			if (onScene->type() == Vertex::Type && onScene == currFigure.first()) {
				endFigure();
			}
			return;
		}
		else {
			addNextEdge(currPos);
		}
	}
}

void GraphWidget::beginFigure(const QPointF & currPos)
{
	currFigure.clear();
	Vertex * vertex = new Vertex(this);
	vertex->setPos(currPos);
	scene->addItem(vertex);
	currFigure << vertex;
}

void GraphWidget::addNextEdge(const QPointF & currPos)
{
	Vertex * vertex = new Vertex(this);
	vertex->setPos(currPos);
	double u = QInputDialog::getDouble(this, tr("Input tempertature"),
									   tr("Temperature"), 100, 0);

	Edge * edge = new Edge(currFigure.last(), vertex, u);

	scene->addItem(vertex);
	scene->addItem(edge);

	currFigure << vertex;
}

void GraphWidget::endFigure()
{
	double u = QInputDialog::getDouble(this, tr("Input tempertature"),
									   tr("Temperature"), 100, 0);
	Edge * edge = new Edge(currFigure.last(), currFigure.first(), u);
	scene->addItem(edge);

	allFigures << currFigure;
	currFigure.clear();
}
