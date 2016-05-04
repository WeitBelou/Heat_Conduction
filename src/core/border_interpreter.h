/**
  *@file
  *Основная цель данного класса - создание заполнение ArgumentForCalc c
  * переменными Layer zeroLayer, BoolNet idNet, double xStep и double yStep,
  * заполненными в соответсвии с интерпетацией данных, полученных из
  * QVector<Border> Borders; все остальные переменные инициализируются тестовыми
  * значениями.
  */


#ifndef BORDER_INTERPRETER_H
#define BORDER_INTERPRETER_H

#include "tfgeometry.h"
#include "border.h"
#include <limits>
#include <cmath>
#include <QPointF>
#include <QVector>



class BorderInterpreter : public QObject
{
	Q_OBJECT
public:
	explicit BorderInterpreter(QObject * parent = 0);
	BorderInterpreter(const QVector<Border> & borders,
					   const int maxPointsPerDimension = 700,
					   const int minPointsPerDimension = 100,
					   const int minPointsBetweenBorders = 10,
					   QObject* parent = 0);
	void solve();
	~BorderInterpreter();
	TFGeometry workingArea() const;

	signals:
	void logSent(const QString& s);

private:
	void findAreaParameters();
	void findLengthHeight();
	void findMinimalDistances();
	void findStep();
	void makeGrid();
	void drawBorders(int accuracy = 200);
	void paintBlankArea(QVector<QPoint>& vector1, QVector<QPoint>& vector2);

	QPoint pToGp(const Point& p);
	QPoint movePoint(const QPoint& p1, const QPoint& p2);

	void putPoint(const QPoint& p, const double& u);

	const int m_maxPointsPerDimension;
	const int m_minPointsPerDimension;
	const int m_minPointsBetweenBorders;


	QVector<Border> borders;
	TFGeometry m_workingArea;
	double xMax, xMin, yMax, yMin;
	int iMax, jMax;
	double length, height, xMinDist, yMinDist;
};

#endif // BORDER_INTERPRETER_H
