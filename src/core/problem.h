#ifndef PROBLEM_H
#define PROBLEM_H
#include "material.h"
#include "tfdynamics.h"
#include "tfgeometry.h"
#include <QObject>
#include "./tfdynamics.h"
#include "./layer.h"
#include <QVector>
#include <exception>
#include <iostream>

class Problem: public QObject
{
	Q_OBJECT
public:
	explicit Problem (QObject *parent = 0);
	Problem(const Material & material, const TFGeometry & geometry,
			double tMax, double tStep, QObject * parent = 0);
	TFDynamics solve() const;
	~Problem();

private:
	const TemperatureField nextTF(const TemperatureField & currentTF) const;

	Material material;
	TFGeometry geometry;
	double m_tMax;
	double m_tStep;

	double Ax;
	double Cx;
	double Bx;

	double Ay;
	double Cy;
	double By;

signals:
	void oneLayerCalcSignal(double executionState) const;
public slots:
};

#endif // PROBLEM_H
