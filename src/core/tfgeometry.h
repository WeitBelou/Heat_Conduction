#ifndef TFGEOMETRY_H
#define TFGEOMETRY_H
#include "layer.h"

class TFGeometry
{
public:
	TFGeometry();
	TFGeometry(const Layer & zeroLayer, const BoolNet & idNet);
	TFGeometry(const Layer & zeroLayer, const BoolNet & idNet,
				 int xStep, int yStep);
	TFGeometry(const TFGeometry & other);

	const TFGeometry operator =(const TFGeometry & other);

	Layer zeroLayer() const;
	void setZeroLayer(const Layer& zeroLayer);

	BoolNet idNet() const;
	void setIdNet(const BoolNet& idNet);

	double xStep() const;
	void setXStep(double xStep);

	double yStep() const;
	void setYStep(double yStep);

	int iMax() const;

	int jMax() const;

private:
	Layer m_zeroLayer;
	BoolNet m_idNet;

	double m_xStep;
	double m_yStep;

	int m_iMax;
	int m_jMax;
};
#endif // TFGEOMETRY_H
