#ifndef ARGUMENT_H
#define ARGUMENT_H
#include "./layer.h"
#include <QVector>

class Argument
{
public:
	Argument();
	Argument(double tMax, double tStep,
			 double p = 7800, double lambda = 46, double c = 460);
	~Argument();

	double tMax() const;
	void setTMax(double tMax);

	double tStep() const;
	void setTStep(double tStep);

	double p() const;
	void setP(double p);

	double lambda() const;
	void setLambda(double lambda);

	double c() const;
	void setC(double c);

private:
	double m_tMax;
	double m_tStep;

	double m_p;
	double m_lambda;
	double m_c;
};

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
