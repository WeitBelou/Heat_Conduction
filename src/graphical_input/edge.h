#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Vertex;

class Edge : public QGraphicsItem
{
public:
	Edge(Vertex *sourceNode, Vertex *destNode);

	Vertex *sourceNode() const;
	Vertex *destNode() const;

	void adjust();

	enum { Type = UserType + 2 };
    int type() const Q_DECL_OVERRIDE { return Type; };
    QPainterPath shape() const override;

protected:
	QRectF boundingRect() const Q_DECL_OVERRIDE;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

private:
	Vertex *source, *dest;

	QPointF sourcePoint;
	QPointF destPoint;   
};

#endif // EDGE_H
