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
};

#endif // PROBLEM_H
