#include "edge.h"
#include "vertex.h"

#include <QPainter>
#include <QInputDialog>

Edge::Edge(Vertex *sourceNode, Vertex *destNode, double u)
	:m_u(u)
{
	setAcceptedMouseButtons(0);
	source = sourceNode;
	dest = destNode;
	source->setSecondEdge(this);
	dest->setFirstEdge(this);
	adjust();
}

Vertex *Edge::sourceNode() const
{
	return source;
}

Vertex *Edge::destNode() const
{
	return dest;
}

void Edge::adjust()
{
	if (!source || !dest)
		return;

	QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
	qreal length = line.length();

	prepareGeometryChange();

	if (length > 0) {
		m_sourcePoint = line.p1();
		m_destPoint = line.p2();
	} else {
		m_sourcePoint = m_destPoint = line.p1();
	}
}

QRectF Edge::boundingRect() const
{
	if (!source || !dest)
		return QRectF();

	qreal extra = 0.01;

	return QRectF(m_sourcePoint, QSizeF(m_destPoint.x() - m_sourcePoint.x(),
									  m_destPoint.y() - m_sourcePoint.y()))
		.normalized()
		.adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (!source || !dest)
		return;

	QLineF line(m_sourcePoint, m_destPoint);
	if (qFuzzyCompare(line.length(), qreal(0.)))
		return;

	painter->setPen(QPen(Qt::black, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter->drawLine(line);
}

QPainterPath Edge::shape() const
{
    if (!source || !dest)
        return QPainterPath();

    QPainterPath path;
    QVector<QPointF> polygon;
    polygon << sourcePoint << destPoint;
    path.addPolygon(polygon);
    return path;
}

QPointF Edge::destPoint() const
{
	return m_destPoint;
}

QPointF Edge::sourcePoint() const
{
	return m_sourcePoint;
}

double Edge::u() const
{
	return m_u;
}

