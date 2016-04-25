#include "problem.h"

Problem::Problem()
{

}


Problem::Problem(const Material & material, const TFGeometry & TFGeometry,
		double tMax, double tStep)
{
	m_material = material;
	m_TFGeometry = TFGeometry;
	m_tMax = tMax;
	m_tStep = tStep;
	const double m_Ax = material.lambda()/(TFGeometry.xStep() * TFGeometry.xStep());
	const double m_Cx = material.lambda()/(TFGeometry.xStep() * TFGeometry.xStep());
	const double m_Bx = 2*material.lambda()/(TFGeometry.xStep() * TFGeometry.xStep())
						+ material.rho()*material.c()/tStep;


	const double m_Ay = material.lambda()/(TFGeometry.yStep() * TFGeometry.yStep());
	const double m_Cy = material.lambda()/(TFGeometry.yStep() * TFGeometry.yStep());
	const double m_By = 2*material.lambda()/(TFGeometry.yStep() * TFGeometry.yStep())
						+ material.rho()*material.c()/tStep;
}


const TemperatureField Problem::nextTF(const TemperatureField & currentTF) const
{

}

TFDynamics Problem::solve() const
{
	const TemperatureField zeroLayer = TFGeometry.zeroLayer();
	const BoolGrid idNet = TFGeometry.idNet();
	int iMax = TFGeometry.iMax();
	int jMax = TFGeometry.jMax();
	double tStep = m_tStep;
	double tMax = m_tMax;
	double xStep = TFGeometry.xStep();
	double yStep = TFGeometry.yStep();
	double rho = Material.rho();
	double lambda = Material.lambda();
	double c = Material.c();
	double executionState;

	TemperatureField alpha(iMax, jMax);
	TemperatureField beta(iMax, jMax);

//!
	TFDynamics allLayers(tMax + 1, TemperatureField(iMax, jMax));
	allLayers[0] = zeroLayer;
//!





// расчитаем коэфициенты, которые будут постоянны на протяжении всего расчёта


double newAlpha; // переменные для временного хранения промежуточных значений
double newBeta;
double F;

f
}


Problem::~Problem()
{

}


