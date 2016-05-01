#include "edge.h"
#include "vertex.h"
#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

Vertex::Vertex(GraphWidget *graphWidget)
	: graph(graphWidget), radius(5)
{
	setFlag(ItemSendsGeometryChanges);
	setFlag(ItemIgnoresTransformations);
	setAcceptHoverEvents(true);
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
	return QRectF( -radius - adjust, -radius - adjust, 2 * radius + adjust, 2 * radius + adjust);
}

QPainterPath Vertex::shape() const
{
	QPainterPath path;
	path.addEllipse(-radius, -radius, 2 * radius, 2 * radius);
	return path;
}

void Vertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->setPen(Qt::black);
	painter->setBrush(Qt::darkGray);
	painter->drawEllipse(-radius, -radius, 2 * radius, 2 * radius);
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


void Vertex::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
	prepareGeometryChange();
	radius = 10;
}

void Vertex::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
	prepareGeometryChange();
	radius = 5;
}
