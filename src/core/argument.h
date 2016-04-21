#ifndef ARGUMENT_H
#define ARGUMENT_H
#include "./layer.h"
#include <QVector>
class ArgumentForCalc
{
public:
	ArgumentForCalc();
	ArgumentForCalc(const Layer & zeroLayer, const BoolNet & idNet,
					int tMax,
					double tStep,double xStep, double yStep,
					double p, double lmbd, double c);
	void operator =(const ArgumentForCalc & anotherArgumentForCalc);
	Layer zeroLayer;
	BoolNet idNet;
	int tMax;
	int iMax;
	int jMax;
	double tStep;
	double xStep;
	double yStep;
	double p;
	double lmbd;
	double c;
};


class ArgumentForDraw
{
public:
	ArgumentForDraw();
	ArgumentForDraw(const QVector<Layer> allLayers,
					int tMax,double tStep,double xStep, double yStep);
	void operator =(const ArgumentForDraw & anotherArgumentForDraw);
	QVector<Layer> allLayers;
	int tMax;
	int iMax;
	int jMax;
	double tStep;
	double xStep;
	double yStep;
};





#endif // ARGUMENT_H
