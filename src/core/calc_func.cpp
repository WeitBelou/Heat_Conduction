// || - или
// && - и
#include "calc_func.h"
// (lmbd) lambda for heat capacity, p for density, c for thermal conductivity
vector <Layer> calculateAllLayers(const Layer  & zeroLayer, const BoolNet & idNet,
						  int tMax, double tStep, double xStep, double yStep,
						  double p, double lmbd, double c)
{
vector<Layer> allLayers(tMax+1);
allLayers.push_back(zeroLayer);

if ((zeroLayer.getImax() != idNet.getImax()) || ((zeroLayer.getJmax() != idNet.getJmax())))
	throw std::range_error("Размеры матрицы температур и битовой сетки не совпадают!");

int iMax = zeroLayer.getImax();
int jMax = zeroLayer.getJmax();

Layer alpha(iMax, jMax);
Layer beta(iMax, jMax);



// расчитаем коэфициенты, которые будут постоянны на протяжении всего расчёта
double Ax = lmbd/(xStep*xStep);
double & Cx = Ax;
double Bx = 2*lmbd/(xStep*xStep) + p*c/tStep;

double Ay = lmbd/(yStep*yStep);
double & Cy = Ay;
double By = 2*lmbd/(yStep*yStep) + p*c/tStep;

double newAlpha; // переменные для временного хранения промежуточных значений
double newBeta;
double F;
// на шаге tMax-1 будет расчитано значние температур для слоя tMax
for (int t = 0; t <tMax; t ++)
{
	//alpha and beta calculation
	for (int j = 0; j < jMax; j++ ) //выбираем строку (движемся между строк)
	{
		for (int i = 0; i <iMax; i++) // выбираем элемент в строке (движемся по строке)
		{
			if ((!idNet(i,j))) // если этот элемент граница, а справа - уже нет, то расчитываем коэф. по формуле (8)
				alpha(i,j) = 0; beta(i,j) = allLayers[t](i,j);

			if (idNet(i,j))
			{
				newAlpha = Ax/(Bx-Cx*alpha(i-1,j));
				alpha(i,j) = newAlpha;
				F = -((p*c)/tStep)*allLayers[t](i,j);
				newBeta = (Cx*beta(i-1,j)-F)/(Bx-Cx*alpha(i-1,j));
				beta(i,j) = newBeta;
			}
			// возможно, стоит отдельно обрабатывать и случай правой границы
		}
	}
	// на этом шаге мы высчитали альфа и бета для t = t + 1/2 * tau;
	// расчитаем ряд температур. Потом размажем и повторим

	for (int j = 0; j < jMax; j++) //выбираем cтолбец (движемся между стобцов)
	{
		for (int i = iMax-1; i >=0; i--) // выбираем элемент в столбце (движемся по стобцу)
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
			if ((!idNet(i,j))) // если этот элемент граница, а справа - уже нет, то расчитываем коэф. по формуле (8)
				alpha(i,j) = 0; beta(i,j) = allLayers[t](i,j);

			if (idNet(i,j))
			{
				newAlpha = Ay/(By-Cy*alpha(i,j-1));
				alpha(i,j) = newAlpha;
				F = -((p*c)/tStep)*allLayers[t](i,j);
				newBeta = (Cy*beta(i,j-1)-F)/(By-Cy*alpha(i,j-1));
				beta(i,j) = newBeta;
			}
			// возможно, стоит отдельно обрабатывать и случай правой границы
		}
	}
	// на этом шаге мы высчитали альфа и бета для t = t + tau;
	// расчитаем ряд температур. Потом размажем и повторим

	for (int i = 0; i < iMax; i++) //выбираем строку (движемся между строк)
	{
		for (int j = jMax-1; j >=0; j--) // выбираем элемент в строке (движемся по строке)
		{
			if (!idNet(i,j)) //граница
				allLayers[t+1](i,j) = allLayers[t](i,j);
			if (idNet(i,j))
				allLayers[t+1](i,j) = allLayers[t+1](i,j+2)*alpha(i,j) + beta (i,j);
		}
	}

}

return allLayers;
}
