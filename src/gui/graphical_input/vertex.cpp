#include "edge.h"
#include "vertex.h"
#include "graphwidget.h"

Vertex::Vertex(GraphWidget *graphWidget)
	: graph(graphWidget), radius(5),
	  m_firstEdge(nullptr), m_secondEdge(nullptr)
{
	setFlag(ItemSendsGeometryChanges);
	setFlag(ItemIgnoresTransformations);
	setAcceptHoverEvents(true);
	setCacheMode(DeviceCoordinateCache);
	setZValue(-1);
}

int Vertex::type() const
{
	return Type;
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
		if (firstEdge()) {
			firstEdge()->adjust();
		}
		if (secondEdge()){
			secondEdge()->adjust();
		}
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

Edge * Vertex::secondEdge() const
{
	return m_secondEdge;
}

void Vertex::setSecondEdge(Edge * secondEdge)
{
	m_secondEdge = secondEdge;
}

Edge * Vertex::firstEdge() const
{
	return m_firstEdge;
}

void Vertex::setFirstEdge(Edge * firstEdge)
{
	m_firstEdge = firstEdge;
}
