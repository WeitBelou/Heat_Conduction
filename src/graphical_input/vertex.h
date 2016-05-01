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

	void addEdge(Edge *edge);
	QList<Edge *> edges() const;

	enum { Type = UserType + 1 };
	int type() const override { return Type; }

	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
	QList<Edge *> edgeList;
	QPointF newPos;
	GraphWidget *graph;
};

#endif // VERTEX_H