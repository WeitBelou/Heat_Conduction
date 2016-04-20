#include "./layer.h"
#include <QVector>
#include "./argument.h"

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
