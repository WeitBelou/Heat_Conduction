#ifndef ARGUMENT_STRUCT_H
#define ARGUMENT_STRUCT_H
#include "./layer.h"
struct ArgumentForCalc
{	const Layer zeroLayer;
	const BoolNet idNet;
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

struct ArgumentForDraw
{
	const QVector<Layer> allLayers;
	int tMax;
	int iMax;
	int jMax;
	double tStep;
	double xStep;
	double yStep;
};

#endif // ARGUMENT_STRUCT_H
