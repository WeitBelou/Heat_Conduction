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
#include <QFile>
#include <QDebug>


class BorderInterpreter : public QObject
{
	Q_OBJECT
public:
	BorderInterpreter(QObject * parent = 0);
	BorderInterpreter(const QVector<Border> & Borders,
					   const int maxPointsPerDimension = 1000,
					   const int minPointsPerDimension = 100,
					   const int minPointsBetweenBorders = 10,
					   QObject * parent = 0);
	~BorderInterpreter();
	TFGeometry workingArea() const;

private:
	void findAreaParameters(const QVector<Border>& Borders);
	void makeGrid();
	void drawBorders(const QVector<Border>& Borders, int accuracy = 200);
	void paintBlankArea(QVector<GridPoint>& set1, QVector<GridPoint>& set2);

	GridPoint pToGp(const Point& p);
	GridPoint movePoint(const GridPoint& p1, const GridPoint& p2);

	void putPoint(const GridPoint& p, const double& u);

	const int m_maxPointsPerDimension;
	const int m_minPointsPerDimension;
	const int m_minPointsBetweenBorders;

	QTextStream logstream;
	QString logpath;

	TFGeometry m_workingArea;
	double xMax, xMin, yMax, yMin;
	int iMax, jMax;
	double length, height, xMinDist, yMinDist;
};

#endif // BORDER_INTERPRETER_H
