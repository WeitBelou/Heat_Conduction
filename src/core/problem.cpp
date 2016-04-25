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


	QVector<TemperatureField> allLayers(tMax + 1, TemperatureField(iMax, jMax));
	allLayers[0] = zeroLayer;

	if ((zeroLayer.iMax() != idNet.iMax()) || ((zeroLayer.jMax() != idNet.jMax())))
		throw std::range_error("Размеры матрицы температур и битовой сетки не совпадают!");





// расчитаем коэфициенты, которые будут постоянны на протяжении всего расчёта
const double Ax = lambda/(xStep*xStep);
const double Cx = Ax;
const double Bx = 2*lambda/(xStep*xStep) + p*c/tStep;

const double Ay = lambda/(yStep*yStep);
const double Cy = Ay;
const double By = 2*lambda/(yStep*yStep) + p*c/tStep;

double newAlpha; // переменные для временного хранения промежуточных значений
double newBeta;
double F;
}


Problem::~Problem()
{

}


