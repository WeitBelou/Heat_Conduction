#include "./layer.h"
#include <QVector>
#include "./argument.h"

/*****************************************************************************/
Argument::Argument()
{
	///Set default values for steel
	setTMax(10);
	setTStep(0.1);
	setP(7800);
	setLambda(46);
	setC(460);
}

Argument::Argument(double tMax, double tStep, double p, double lambda, double c)
{
	setTMax(tMax);
	setTStep(tStep);
	setP(p);
	setLambda(lambda);
	setC(c);
}

Argument::~Argument()
{

}

double Argument::tMax() const
 {
	 return m_tMax;
 }

 void Argument::setTMax(double tMax)
 {
	 m_tMax = tMax;
 }

 double Argument::tStep() const
 {
	 return m_tStep;
 }

 void Argument::setTStep(double tStep)
 {
	 m_tStep = tStep;
 }

 double Argument::p() const
 {
	 return m_p;
 }

 void Argument::setP(double p)
 {
	 m_p = p;
 }

 double Argument::lambda() const
 {
	 return m_lambda;
 }

 void Argument::setLambda(double lambda)
 {
	 m_lambda = lambda;
 }

 double Argument::c() const
 {
	 return m_c;
 }

 void Argument::setC(double c)
 {
	 m_c = c;
 }

 /*****************************************************************************/

 ArgumentForCalc::ArgumentForCalc()
 {

 }

 ArgumentForCalc::ArgumentForCalc(const Layer & zeroLayer, const BoolNet & idNet,
								  int tMax,
								  double tStep,double xStep, double yStep,
								  double p, double lmbd, double c)
 {
	 this->zeroLayer= zeroLayer;
	 this->idNet = idNet;
	 this -> tMax = tMax;
	 this -> iMax = zeroLayer.getImax();
	 this -> jMax = zeroLayer.getJmax();
	 this -> tStep = tStep;
	 this -> xStep = xStep;
	 this -> yStep = yStep;
	 this -> p = p;
	 this -> lmbd = lmbd;
	 this -> c = c;
 }

 void ArgumentForCalc::operator =(const ArgumentForCalc & anotherArgumentForCalc)
 {
	 this->zeroLayer= anotherArgumentForCalc.zeroLayer;
	 this->idNet = anotherArgumentForCalc.idNet;
	 this -> tMax = anotherArgumentForCalc.tMax;
	 this -> iMax = anotherArgumentForCalc.zeroLayer.getImax();
	 this -> jMax = anotherArgumentForCalc.zeroLayer.getJmax();
	 this -> tStep = anotherArgumentForCalc.tStep;
	 this -> xStep = anotherArgumentForCalc.xStep;
	 this -> yStep = anotherArgumentForCalc.yStep;
	 this -> p = anotherArgumentForCalc.p;
	 this -> lmbd = anotherArgumentForCalc.lmbd;
	 this -> c = anotherArgumentForCalc.c;


 }

 ArgumentForDraw::ArgumentForDraw()
 {

 }



 ArgumentForDraw::ArgumentForDraw(const QVector<Layer> allLayers,
								  int tMax,double tStep,double xStep, double yStep)
 {
	 this -> allLayers = allLayers;
	 this -> tMax = tMax;
	 this -> iMax = allLayers[0].getImax();
	 this -> jMax = allLayers[0].getJmax();
	 this -> tStep = tStep;
	 this -> xStep = xStep;
	 this -> yStep = yStep;
 }

  void ArgumentForDraw::operator =(const ArgumentForDraw & anotherArgumentForDraw)
 {
	  this ->allLayers =  anotherArgumentForDraw.allLayers;
	  this -> tMax = anotherArgumentForDraw.tMax;
	  this -> iMax = anotherArgumentForDraw.iMax;
	  this -> jMax = anotherArgumentForDraw.jMax;
	  this -> tStep =  anotherArgumentForDraw.tStep;
	  this -> xStep =  anotherArgumentForDraw.xStep;
	  this -> yStep =  anotherArgumentForDraw.yStep;


 }
