#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
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
	void createScene();
	void drawGrid(QPainter *painter, const QRectF &rect);

	QGraphicsScene * scene;

	Vertex * currVertex;
	QVector<Border> currFigure;
};

#endif // GRAPHWIDGET_H
