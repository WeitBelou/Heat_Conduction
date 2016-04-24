#include "tfgeometry.h"

TFGeometry::TFGeometry()
{
	m_zeroLayer = TemperatureField();
	m_idNet = BoolGrid();

	m_xStep = 1;
	m_yStep = 1;

	m_iMax = m_idNet.iMax();
	m_jMax = m_idNet.jMax();
}

TFGeometry::TFGeometry(const TemperatureField& zeroLayer, const BoolGrid& idNet)
{
	m_zeroLayer = zeroLayer;
	m_idNet = idNet;

	m_xStep = 1;
	m_yStep = 1;

	m_iMax = m_idNet.iMax();
	m_jMax = m_idNet.jMax();
}

TFGeometry::TFGeometry(const TemperatureField& zeroLayer, const BoolGrid& idNet,
						   int xStep, int yStep)
{
	m_zeroLayer = zeroLayer;
	m_idNet = idNet;

	m_xStep = xStep;
	m_yStep = yStep;

	m_iMax = m_idNet.iMax();
	m_jMax = m_idNet.jMax();
}

TFGeometry::TFGeometry(const TFGeometry& other)
{
	m_zeroLayer = other.zeroLayer;
	m_idNet = other.idNet();

	m_xStep = other.xStep();
	m_yStep = other.yStep();

	m_iMax = other.iMax();
	m_jMax = other.jMax();
}

const TFGeometry TFGeometry::operator =(const TFGeometry& other)
{
	setZeroLayer(other.zeroLayer());
	setIdNet(other.idNet());

	setXStep(other.xStep());
	setYStep(other.yStep());

	m_iMax = other.iMax();
	m_jMax = other.jMax();

	return *this;
}

TemperatureField TFGeometry::zeroLayer() const
{
	return m_zeroLayer;
}

void TFGeometry::setZeroLayer(const TemperatureField& zeroLayer)
{
	m_zeroLayer = zeroLayer;
}

BoolGrid TFGeometry::idNet() const
{
	return m_idNet;
}

void TFGeometry::setIdNet(const BoolGrid& idNet)
{
	m_idNet = idNet;
}

double TFGeometry::xStep() const
{
	return m_xStep;
}

void TFGeometry::setXStep(double xStep)
{
	m_xStep = xStep;
}

double TFGeometry::yStep() const
{
	return m_yStep;
}

void TFGeometry::setYStep(double yStep)
{
	m_yStep = yStep;
}

int TFGeometry::iMax() const
{
	return m_iMax;
}

int TFGeometry::jMax() const
{
	return m_jMax;
}

