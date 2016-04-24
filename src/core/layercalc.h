#ifndef LAYERCALC_H
#define LAYERCALC_H

#include <QObject>
#include "./tfdinamics.h"
#include "./layer.h"
#include <QVector>
#include <exception>
#include <iostream>

class LayerCalc : public QObject
{
	Q_OBJECT
public:
	explicit LayerCalc(QObject *parent = 0);
	ArgumentForDraw operator()(ArgumentForCalc const & argument);
signals:
	void oneLayerCalcSignal(double executionState);
public slots:
};

#endif // LAYERCALC_H
