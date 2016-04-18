// || - или
// && - и
#include "calc_func.h"
#include "./argument.h"
// (lmbd) lambda for heat capacity, p for density, c for thermal conductivity
ArgumentForDraw calculateAllLayers( ArgumentForCalc const & argument)
{


	const Layer zeroLayer = argument.zeroLayer;
	const BoolNet idNet = argument.idNet;
	int tMax = argument.tMax;
	int iMax = argument.iMax;
	int jMax = argument.jMax;
	double tStep = argument.tStep;
	double xStep = argument.xStep;
	double yStep = argument.yStep;
	double p = argument.p;
	double lmbd = argument.lmbd;
	double c = argument.c;

	Layer alpha(iMax, jMax);
	Layer beta(iMax, jMax);


	QVector<Layer> allLayers(tMax + 1, Layer(iMax, jMax));
	allLayers[0] = zeroLayer;

	if ((zeroLayer.getImax() != idNet.getImax()) || ((zeroLayer.getJmax() != idNet.getJmax())))
		throw std::range_error("Размеры матрицы температур и битовой сетки не совпадают!");





// расчитаем коэфициенты, которые будут постоянны на протяжении всего расчёта
const double Ax = lmbd/(xStep*xStep);
const double Cx = Ax;
const double Bx = 2*lmbd/(xStep*xStep) + p*c/tStep;

const double Ay = lmbd/(yStep*yStep);
const double Cy = Ay;
const double By = 2*lmbd/(yStep*yStep) + p*c/tStep;

double newAlpha; // переменные для временного хранения промежуточных значений
double newBeta;
double F;
// на шаге tMax-1 будет расчитано значние температур для слоя tMax

for (int t = 0; t <tMax; t ++)
{

	//alpha and beta calculation

	for (int j = 0; j < jMax; j++ )
	{
		for (int i = 0; i <iMax; i++)
		{
			if ((!idNet(i,j)))
				alpha(i,j) = 0; beta(i,j) = allLayers[t](i,j);

			if (idNet(i,j))
			{
				newAlpha = Ay/(By-Cy*alpha(i-1,j));
				alpha(i,j) = newAlpha;
				F = -((p*c)/tStep)*allLayers[t](i,j);
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
			if (!idNet(i,j)) //граница
				allLayers[t+1](i,j) = allLayers[t](i,j);
			if (idNet(i,j))
				allLayers[t+1](i,j) = allLayers[t+1](i+1,j)*alpha(i,j) + beta (i,j);
		}
	}

		// на этом шаге мы высчитали T для t = t + 1/2 * tau;
		// теперь повторим то же самое горизонтально

	for (int i = 0; i < iMax; i++ ) //выбираем строку (движемся между строк)
	{
		for (int j = 0; j <jMax; j++) // выбираем элемент в строке (движемся по строке)
		{
			if ((!idNet(i,j)))
				alpha(i,j) = 0; beta(i,j) = allLayers[t](i,j);

			if (idNet(i,j))
			{
				newAlpha = Ax/(Bx-Cx*alpha(i,j-1));
				alpha(i,j) = newAlpha;
				F = -((p*c)/tStep)*allLayers[t+1](i,j);
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
			if (!idNet(i,j)) //граница
				allLayers[t+1](i,j) = allLayers[t](i,j);
			if (idNet(i,j))
				allLayers[t+1](i,j) = allLayers[t+1](i,j+1)*alpha(i,j) + beta (i,j);
		}
	}

}

return ArgumentForDraw (allLayers, tMax, tStep, xStep, yStep);
}
