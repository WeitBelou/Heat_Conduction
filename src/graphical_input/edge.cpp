#include "edge.h"
#include "vertex.h"

#include <QPainter>
#include <QInputDialog>

Edge::Edge(Vertex *sourceNode, Vertex *destNode, double u)
	:u(u)
{
	setAcceptedMouseButtons(0);
	source = sourceNode;
	dest = destNode;
	source->addEdge(this);
	dest->addEdge(this);
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
		sourcePoint = line.p1();
		destPoint = line.p2();
	} else {
		sourcePoint = destPoint = line.p1();
	}
}

QRectF Edge::boundingRect() const
{
	if (!source || !dest)
		return QRectF();

	qreal extra = 0.01;

	return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
									  destPoint.y() - sourcePoint.y()))
		.normalized()
		.adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (!source || !dest)
		return;

	QLineF line(sourcePoint, destPoint);
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
