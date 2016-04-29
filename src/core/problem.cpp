#include "problem.h"
#include "material.h"
#include "tfdynamics.h"
#include "tfgeometry.h"
#include <QObject>
#include "./tfdynamics.h"
#include "./layer.h"
#include <QVector>

#include <iostream>
#include <omp.h>
#include <time.h>
Problem::Problem(QObject *parent) : QObject(parent)
{

}


Problem::Problem(const Material & material, const TFGeometry & geometry,
		double tMax, double tStep, QObject *parent) : QObject(parent)
{
	this->material = material;
	this->geometry = geometry;
	m_tMax = tMax;
	m_tStep = tStep;
	Ax = material.lambda()/(geometry.xStep() * geometry.xStep());
	Cx = material.lambda()/(geometry.xStep() * geometry.xStep());
	Bx = 2*material.lambda()/(geometry.xStep() * geometry.xStep())
						+ material.rho()*material.c()/m_tStep;


	Ay = material.lambda()/(geometry.yStep() * geometry.yStep());
	Cy = material.lambda()/(geometry.yStep() * geometry.yStep());
	By = 2*material.lambda()/(geometry.yStep() * geometry.yStep())
						+ material.rho()*material.c()/m_tStep;
}

const TemperatureField Problem::nextTF(const TemperatureField & current) const
{
	TemperatureField next (current.iMax(), current.jMax());

	int iMax = geometry.iMax();
	int jMax = geometry.jMax();
	const double rho = material.rho();
	const double c = material.c();



	TemperatureField alpha(iMax, jMax);
	TemperatureField beta(iMax, jMax);


#pragma omp parallel for
	for (int j = 0; j < jMax; j++ )
	{
		double F;
		double newAlpha;
		double newBeta;
		for (int i = 0; i <iMax; i++)
		{

			if ((!geometry.idNet()(i, j)))
				alpha(i,j) = 0; beta(i,j) = current(i,j);

			if (geometry.idNet()(i, j))
			{
				newAlpha = Ay/(By-Cy*alpha(i-1,j));
				alpha(i,j) = newAlpha;
				F = -((rho*c)/m_tStep)*current(i,j);
				newBeta = (Cy*beta(i-1,j)-F)/(By-Cy*alpha(i-1,j));
				beta(i,j) = newBeta;
			}

		}
	}
	// на этом шаге мы высчитали альфа и бета для t = t + 1/2 * tau;
	// расчитаем ряд температур. Потом размажем и повторим

#pragma omp parallel for
	for (int j = 0; j < jMax; j++)
	{
		for (int i = iMax-1; i > -1; i--)
		{
			if (!geometry.idNet()(i, j)) //граница
				next(i,j) = current(i,j);
			if (geometry.idNet()(i, j))
				next(i,j) = next(i+1,j)*alpha(i,j) + beta (i,j);
		}
	}

		// на этом шаге мы высчитали T для t = t + 1/2 * tau;
		// теперь повторим то же самое горизонтально

#pragma omp parallel for
	for (int i = 0; i < iMax; i++ ) //выбираем строку (движемся между строк)
	{
		double F;
		double newAlpha;
		double newBeta;
		for (int j = 0; j <jMax; j++) // выбираем элемент в строке (движемся по строке)
		{

			if ((!geometry.idNet()(i, j)))
				alpha(i,j) = 0; beta(i,j) = current(i,j);

			if (geometry.idNet()(i, j))
			{
				newAlpha = Ax/(Bx-Cx*alpha(i,j-1));
				alpha(i,j) = newAlpha;
				F = -((rho*c)/m_tStep)*next(i,j);
				newBeta = (Cx*beta(i,j-1)-F)/(Bx-Cx*alpha(i,j-1));
				beta(i,j) = newBeta;
			}

		}
	}
	// на этом шаге мы высчитали альфа и бета для t = t + tau;
	// расчитаем ряд температур. Потом размажем и повторим

#pragma omp parallel for
	for (int i = 0; i < iMax; i++) //выбираем строку (движемся между строк)
	{
		for (int j = jMax-1; j > -1; j--) // выбираем элемент в строке (движемся по строке)
		{
			if (!geometry.idNet()(i, j)) //граница
				next(i,j) = current(i,j);
			if (geometry.idNet()(i, j))
				next(i,j) = next(i,j+1)*alpha(i,j) + beta (i,j);
		}
	}
	return next;
}

TFDynamics Problem::solve() const
{
	int tMax = m_tMax/m_tStep;
	double executionState;

	double t1 = time(0);
	QVector<TemperatureField> temperatureFields;
	temperatureFields.reserve(tMax + 1);
	temperatureFields.push_back(geometry.zeroLayer());

	TFDynamics allLayers(temperatureFields, m_tStep, geometry.xStep(),
						 geometry.yStep());

	for (int t = 0; t < tMax; t ++)
	{
		allLayers.push_back(nextTF(allLayers[t]));
		executionState = double(t)/double(tMax);
		emit oneLayerCalcSignal(executionState);
	}
	double t2 = time(0);
	std::cout << t2-t1 << std::endl;

return allLayers;
}


Problem::~Problem()
{

}



