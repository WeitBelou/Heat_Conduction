#ifndef PROBLEM_H
#define PROBLEM_H
#include <QObject>
#include <QVector>

#include <QTime>
#include <src/libheat/components/tfgeometry.h>
#include <src/libheat/components/tfdynamics.h>
#include <src/libheat/components/material.h>

class Problem: public QObject
{
	Q_OBJECT
public:
	explicit Problem (QObject *parent = 0);
	Problem(const Material & material, const TFGeometry & geometry,
			float tMax, float tStep, QObject * parent = 0);
	TFDynamics solve() const;
	~Problem();

public slots:
	void stopCalc();

private:
	const TemperatureField nextTF(const TemperatureField & currentTF) const;

	Material material;
	TFGeometry geometry;
	float m_tMax;
	float m_tStep;

	float Ax;
	float Cx;
	float Bx;

	bool isBreak;

signals:
	void layerCalcDone(double executionState) const;
	void calcFinished (double seconds) const;
public slots:
};

#endif // PROBLEM_H
