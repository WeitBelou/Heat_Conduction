#ifndef TFGEOMETRY_H
#define TFGEOMETRY_H
#include "layer.h"

class TFGeometry
{
public:
	TFGeometry();
	TFGeometry(const TemperatureField & zeroLayer, const BoolGrid & idNet);
	TFGeometry(const TemperatureField & zeroLayer, const BoolGrid & idNet,
				 double xStep, double yStep);
	TFGeometry(const TFGeometry & other);

	TFGeometry & operator =(const TFGeometry & other);

	TemperatureField & zeroLayer();
	const TemperatureField & zeroLayer() const;
	void setZeroLayer(const TemperatureField& zeroLayer);

	BoolGrid & idNet();
	const BoolGrid & idNet() const;
	void setIdNet(const BoolGrid& idNet);

	double xStep() const;
	void setXStep(double xStep);

	double yStep() const;
	void setYStep(double yStep);

	int iMax() const;

	int jMax() const;

private:
	TemperatureField m_zeroLayer;
	BoolGrid m_idNet;

	double m_xStep;
	double m_yStep;
};
#endif // TFGEOMETRY_H
