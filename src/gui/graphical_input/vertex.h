#ifndef VERTEX_H
#define VERTEX_H

#include <QGraphicsItem>
#include <QList>

class Edge;
class GraphWidget;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class Vertex : public QGraphicsItem
{
public:
	explicit Vertex(GraphWidget *graphWidget);

	enum { Type = UserType + 1 };
	int type() const override;

	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

	Edge * firstEdge() const;
	void setFirstEdge(Edge * firstEdge);

	Edge * secondEdge() const;
	void setSecondEdge(Edge * secondEdge);

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
	void hoverEnterEvent(QGraphicsSceneHoverEvent * event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) override;

private:
	GraphWidget *graph;
	float radius;

	Edge * m_firstEdge;
	Edge * m_secondEdge;
};

#endif // VERTEX_H
