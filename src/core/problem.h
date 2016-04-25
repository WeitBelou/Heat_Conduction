#ifndef PROBLEM_H
#define PROBLEM_H
#include "material.h"
#include "tfdynamics.h"
#include "tfgeometry.h"
class Problem
{
public:
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

	const double Ax = lambda/(xStep*xStep);
	const double Cx = Ax;
	const double Bx = 2*lambda/(xStep*xStep) + p*c/tStep;

	const double Ay = lambda/(yStep*yStep);
	const double Cy = Ay;
	const double By = 2*lambda/(yStep*yStep) + p*c/tStep;

	double newAlpha; // переменные для временного хранения промежуточных значений
	double newBeta;
	double F;
};

#endif // PROBLEM_H
