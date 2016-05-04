#ifndef PROBLEM_H
#define PROBLEM_H
#include <QObject>
#include <QVector>

#include "material.h"
#include "tfdynamics.h"
#include "tfgeometry.h"
#include "layer.h"

class Problem: public QObject
{
	Q_OBJECT
public:
	explicit Problem (QObject *parent = 0);
	Problem(const Material & material, const TFGeometry & geometry,
			double tMax, double tStep, QObject * parent = 0);
	TFDynamics solve() const;
	~Problem();

public slots:
	void stopCalc();

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

	bool isBreak;

signals:
	void layerCalcDone(double executionState) const;
public slots:
};

#endif // PROBLEM_H
