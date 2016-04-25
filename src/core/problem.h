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
	Problem();
	Problem(const Material & material, const TFGeometry & TFGeometry,
			double tMax, double tStep);
	TFDynamics solve() const;
	~Problem();

private:
	const TemperatureField nextTF(const TemperatureField & currentTF) const;

	Material m_material;
	TFGeometry m_TFGeometry;
	double m_tMax;
	double m_tStep;

	const double Ax;
	const double Cx;
	const double Bx;

	const double Ay;
	const double Cy;
	const double By;

signals:
	void oneLayerCalcSignal(double executionState);
public slots:
};

#endif // PROBLEM_H
