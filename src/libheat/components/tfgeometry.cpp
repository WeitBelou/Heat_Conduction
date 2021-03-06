#include "tfgeometry.h"

TFGeometry::TFGeometry() : m_zeroLayer(), m_idNet(), m_xStep(1), m_yStep(1)
{

}

TFGeometry::TFGeometry(const TemperatureField& zeroLayer, const BoolGrid& idNet) :
	m_zeroLayer(zeroLayer), m_idNet(idNet), m_xStep(1), m_yStep(1)
{

}

TFGeometry::TFGeometry (const TemperatureField &zeroLayer, const BoolGrid &idNet,
						float xStep, float yStep) :
	m_zeroLayer(zeroLayer), m_idNet(idNet), m_xStep(xStep), m_yStep(yStep)
{

}

TFGeometry::TFGeometry(const TFGeometry& other) :
	m_zeroLayer(other.zeroLayer()), m_idNet(other.idNet())
{
	m_xStep = other.xStep();
	m_yStep = other.yStep();
}

TFGeometry & TFGeometry::operator =(const TFGeometry& other)
{
	setZeroLayer(other.zeroLayer());
	setIdNet(other.idNet());

	setXStep(other.xStep());
	setYStep(other.yStep());

	return *this;
}

TemperatureField & TFGeometry::zeroLayer()
{
	return m_zeroLayer;
}

const TemperatureField &TFGeometry::zeroLayer() const
{
	return m_zeroLayer;
}

void TFGeometry::setZeroLayer(const TemperatureField& zeroLayer)
{
	m_zeroLayer = zeroLayer;
}

BoolGrid & TFGeometry::idNet()
{
	return m_idNet;
}

const BoolGrid &TFGeometry::idNet() const
{
	return m_idNet;
}

void TFGeometry::setIdNet(const BoolGrid& idNet)
{
	m_idNet = idNet;
}

float TFGeometry::xStep () const
{
	return m_xStep;
}

void TFGeometry::setXStep(float xStep)
{
	m_xStep = xStep;
}

float TFGeometry::yStep () const
{
	return m_yStep;
}

void TFGeometry::setYStep(float yStep)
{
	m_yStep = yStep;
}

int TFGeometry::iMax() const
{
	return idNet().iMax();
}

int TFGeometry::jMax() const
{
	return idNet().jMax();
}

