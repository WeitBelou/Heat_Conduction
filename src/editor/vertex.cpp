#include "edge.h"
#include "vertex.h"
#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

Vertex::Vertex(GraphWidget *graphWidget)
	: graph(graphWidget)
{
	setFlag(ItemSendsGeometryChanges);
	setCacheMode(DeviceCoordinateCache);
	setZValue(-1);
}

void Vertex::addEdge(Edge *edge)
{
	edgeList << edge;
	edge->adjust();
}

QList<Edge *> Vertex::edges() const
{
	return edgeList;
}

QRectF Vertex::boundingRect() const
{
	qreal adjust = 2;
	return QRectF( -10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath Vertex::shape() const
{
	QPainterPath path;
	path.addEllipse(-10, -10, 20, 20);
	return path;
}

void Vertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->setPen(Qt::black);
	painter->setBrush(Qt::darkGray);
	painter->drawEllipse(-10, -10, 20, 20);
}

QVariant Vertex::itemChange(GraphicsItemChange change, const QVariant &value)
{
	switch (change) {
	case ItemPositionHasChanged:
		foreach (Edge *edge, edgeList)
			edge->adjust();
		break;
	default:
		break;
	};

	return QGraphicsItem::itemChange(change, value);
}

void Vertex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsItem::mousePressEvent(event);
}

void Vertex::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsItem::mouseReleaseEvent(event);
}
