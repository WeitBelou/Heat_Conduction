#include "stdexcept"
#include "problem.h"
#include "material.h"
#include "tfdynamics.h"
#include "tfgeometry.h"
#include <QObject>
#include "./tfdynamics.h"
#include "./layer.h"
#include <QVector>
#include <exception>
#include <iostream>

Problem::Problem()
{

	Material m_material();
	TFGeometry m_TFGeometry();

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

const TemperatureField Problem::nextTF(const TemperatureField & currentTF,
									   TemperatureField & alpha,
									   TemperatureField & beta) const
{
TemperatureField nextTF (currentTF.iMax(), currentTF.jMax());
double F;
double newAlpha;
double newBeta;
for (int j = 0; j < jMax; j++ )
{
	for (int i = 0; i <iMax; i++)
	{
		if ((!TFGeometry.idNet()(i, j)))
			alpha(i,j) = 0; beta(i,j) = currentTF(i,j);

		if (idNet(i,j))
		{
			newAlpha = Ay/(By-Cy*alpha(i-1,j));
			alpha(i,j) = newAlpha;
			F = -((p*c)/tStep)*currentTF(i,j);
			newBeta = (Cy*beta(i-1,j)-F)/(By-Cy*alpha(i-1,j));
			beta(i,j) = newBeta;
		}

	}
}
// на этом шаге мы высчитали альфа и бета для t = t + 1/2 * tau;
// расчитаем ряд температур. Потом размажем и повторим

for (int j = 0; j < jMax; j++)
{
	for (int i = iMax-1; i > -1; i--)
	{
		if (!TFGeometry.idNet()(i, j)) //граница
			nextTF(i,j) = currentTF(i,j);
		if (TFGeometry.idNet()(i, j))
			nextTF(i,j) = nextTF[t+1](i+1,j)*alpha(i,j) + beta (i,j);
	}
}

	// на этом шаге мы высчитали T для t = t + 1/2 * tau;
	// теперь повторим то же самое горизонтально

for (int i = 0; i < iMax; i++ ) //выбираем строку (движемся между строк)
{
	for (int j = 0; j <jMax; j++) // выбираем элемент в строке (движемся по строке)
	{
		if ((!TFGeometry.idNet()(i, j)))
			alpha(i,j) = 0; beta(i,j) = currentTF(i,j);

		if (TFGeometry.idNet()(i, j))
		{
			newAlpha = Ax/(Bx-Cx*alpha(i,j-1));
			alpha(i,j) = newAlpha;
			F = -((p*c)/tStep)*nextTF(i,j);
			newBeta = (Cx*beta(i,j-1)-F)/(Bx-Cx*alpha(i,j-1));
			beta(i,j) = newBeta;
		}
		// возможно, стоит отдельно обрабатывать и случай правой границы
	}
}
// на этом шаге мы высчитали альфа и бета для t = t + tau;
// расчитаем ряд температур. Потом размажем и повторим

for (int i = 0; i < iMax; i++) //выбираем строку (движемся между строк)
{
	for (int j = jMax-1; j > -1; j--) // выбираем элемент в строке (движемся по строке)
	{
		if (!TFGeometry.idNet()(i, j)) //граница
			nextTF(i,j) = currentTF(i,j);
		if (TFGeometry.idNet()(i, j))
			nextTF(i,j) = nextTF(i,j+1)*alpha(i,j) + beta (i,j);
	}
}

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

	QVector<TemperatureField> temperatureFields(tMax + 1, TemperatureField(iMax, jMax));
	temperatureFields[0] = zeroLayer;

	TFDynamics allLayres(temperatureFields, tStep, xStep, yStep);

	for (int t = 0; t < tMax; t ++)
	{
		allLayers.push_back(Problem.nextTF(allLayers[t]));
		executionState = double(t)/double(tMax);
		emit oneLayerCalcSignal(executionState);
	}


return allLayres;
}


Problem::~Problem()
{

}



