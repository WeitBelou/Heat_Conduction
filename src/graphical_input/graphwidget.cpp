#include "graphwidget.h"
#include "edge.h"
#include "vertex.h"
#include <QDebug>

#include <math.h>

#include <QKeyEvent>

GraphWidget::GraphWidget(QWidget *parent)
	: QGraphicsView(parent), maxTemperature(1000)
{
	createScene();
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
	Q_UNUSED(rect);

	QRectF sceneRect = this->sceneRect();

	drawGrid(painter, sceneRect);

	painter->setBrush(QColor(0, 0, 50));
	painter->drawRect(sceneRect);
}

void GraphWidget::createScene()
{
	bool ok;
	double a = QInputDialog::getDouble(this, "Input width", "Width", 10, 1, 1000, 1, &ok);
	if (!ok) {
		emit canceled();
		return;
	}

	double h = QInputDialog::getDouble(this, "Input height", "Height", 10, 1, 1000, 1, &ok);
	if (!ok) {
		emit canceled();
		return;
	}

	maxTemperature = QInputDialog::getDouble(this, "Input max temperatur",
											 "Max Temperature", 1000, 10, 10000, 1, &ok);
	if (!ok) {
		emit canceled();
		return;
	}

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

QColor GraphWidget::colorFromTemperature(double u)
{
//	setColorInterpolation(ciRGB);
//    setColorStopAt(0, QColor(0, 0, 50));
//    setColorStopAt(0.15, QColor(20, 0, 120));
//    setColorStopAt(0.33, QColor(200, 30, 140));
//    setColorStopAt(0.6, QColor(255, 100, 0));
//    setColorStopAt(0.85, QColor(255, 255, 40));
//    setColorStopAt(1, QColor(255, 255, 255));

	double a = 1 - (maxTemperature - u) / maxTemperature;
	if (a > 0.85) {
		a -= 0.85;
		a /= 0.15;
		return QColor(255, 255, 40 + 215 * a);
	}
	if (a > 0.6) {
		a -= 0.6;
		a /= 0.15;
		return QColor(255, 100 + 155 * a, 40 * a);
	}
	if (a > 0.33) {
		a -= 0.33;
		a /= 0.27;
		return QColor(200 + 55 * a, 30 + 70 * a, 140 * (1 - a));
	}
	if (a > 0.15) {
		a -= 0.15;
		a /= 0.18;
		return QColor(20 + 180 * a, 30 * a, 120 + 20 * a);
	}
	if (a >= 0) {
		a /= 0.15;
		return QColor(20 * a, 0, 50 + 70 * a);
	}
	return QColor();
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
									   tr("Temperature"), 100, 0, maxTemperature);

	Edge * edge = new Edge(currFigure.last(), vertex, u);
	edge->setColor(colorFromTemperature(u));

	scene->addItem(vertex);
	scene->addItem(edge);

	currFigure << vertex;
}

void GraphWidget::endFigure()
{
	double u = QInputDialog::getDouble(this, tr("Input tempertature"),
									   tr("Temperature"), 100, 0, maxTemperature);
	Edge * edge = new Edge(currFigure.last(), currFigure.first(), u);
	edge->setColor(colorFromTemperature(u));
	scene->addItem(edge);

	allFigures << currFigure;

	currFigure.clear();
}
