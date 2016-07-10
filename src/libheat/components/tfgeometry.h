#ifndef TFGEOMETRY_H
#define TFGEOMETRY_H
#include "layer.h"

class TFGeometry
{
public:
	TFGeometry();
	TFGeometry(const TemperatureField & zeroLayer, const BoolGrid & idNet);
	TFGeometry (const TemperatureField &zeroLayer, const BoolGrid &idNet,
				float xStep, float yStep);
	TFGeometry(const TFGeometry & other);

	TFGeometry & operator =(const TFGeometry & other);

	TemperatureField & zeroLayer();
	const TemperatureField & zeroLayer() const;
	void setZeroLayer(const TemperatureField& zeroLayer);

	BoolGrid & idNet();
	const BoolGrid & idNet() const;
	void setIdNet(const BoolGrid& idNet);

	float xStep () const;
	void  setXStep(float xStep);

	float yStep () const;
	void  setYStep(float yStep);

	int iMax() const;

	int jMax() const;

private:
	TemperatureField m_zeroLayer;
	BoolGrid m_idNet;

	float m_xStep;
	float m_yStep;
};
#endif // TFGEOMETRY_H
