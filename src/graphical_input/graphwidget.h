#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QtWidgets>
#include <core/border.h>

class Vertex;

class GraphWidget : public QGraphicsView
{
	Q_OBJECT

public:
	explicit GraphWidget(QWidget *parent = 0);

protected:
	void drawBackground(QPainter *painter, const QRectF &rect) override;
	void mousePressEvent(QMouseEvent *mouse) override;

signals:
	void figureCreated(const QVector<Border> & figure);

private:
	void beginFigure(const QPointF & currPos);
	void addNextEdge(const QPointF & currPos);
	void endFigure();

	void createScene();
	void createGrid();
	void drawGrid(QPainter *painter, const QRectF &rect);

	QGraphicsScene * scene;

	QVector<Vertex *> currFigure;
	QVector<QVector<Vertex *> > allFigures;
};

#endif // GRAPHWIDGET_H
