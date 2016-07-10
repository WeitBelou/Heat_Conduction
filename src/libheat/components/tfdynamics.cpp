#include "tfdynamics.h"

TFDynamics::TFDynamics()
{
	m_xStep = 1;
	m_yStep = 1;
	m_tStep = 1;

	m_tMax = 1;
	m_iMax = 1;
	m_jMax = 1;

	createFileStream();
}

TFDynamics::TFDynamics(float tStep)
{
	m_tStep = tStep;
	m_xStep = 1;
	m_yStep = 1;

	m_tMax = 1;
	m_iMax = 1;
	m_jMax = 1;

	createFileStream();
}

TFDynamics::TFDynamics(float tStep, float xStep, float yStep)
{
	m_tStep = tStep;
	m_xStep = xStep;
	m_yStep = yStep;

	m_tMax = 1;
	m_iMax = 1;
	m_jMax = 1;

	createFileStream();
}

TFDynamics::TFDynamics(float tStep, float xStep, float yStep, float tMax, int iMax, int jMax)
{
	m_tStep = tStep;
	m_xStep = xStep;
	m_yStep = yStep;

	m_tMax = tMax;
	m_iMax = iMax;
	m_jMax = jMax;

	createFileStream();
}

TFDynamics::TFDynamics(const TFDynamics & other)
{
	m_fileName = other.m_fileName;

	m_tStep = other.m_tStep;
	m_xStep = other.m_xStep;
	m_yStep = other.m_yStep;

	m_tMax = other.m_tMax;
	m_iMax = other.m_iMax;
	m_jMax = other.m_jMax;
}

TFDynamics::~TFDynamics()
{

}

TFDynamics & TFDynamics::operator =(const TFDynamics & other)
{
	m_fileName = other.m_fileName;

	m_tStep = other.m_tStep;
	m_xStep = other.m_xStep;
	m_yStep = other.m_yStep;

	m_tMax = other.m_tMax;
	m_iMax = other.m_iMax;
	m_jMax = other.m_jMax;

	return *this;
}

float TFDynamics::tStep() const
{
	return m_tStep;
}

void TFDynamics::setTStep(float tStep)
{
	m_tStep = tStep;
}

float TFDynamics::xStep() const
{
	return m_xStep;
}

void TFDynamics::setXStep(float xStep)
{
	m_xStep = xStep;
}

float TFDynamics::yStep() const
{
	return m_yStep;
}

void TFDynamics::setYStep(float yStep)
{
	m_yStep = yStep;
}

void TFDynamics::createFileStream()
{
	m_fileName = QString("BUFFER");
}

float TFDynamics::tMax() const
{
	return m_tMax;
}

void TFDynamics::setTMax(float tMax)
{
	m_tMax = tMax;
}

int TFDynamics::jMax() const
{
	return m_jMax;
}

void TFDynamics::setJMax(int jMax)
{
	m_jMax = jMax;
}

int TFDynamics::iMax() const
{
	return m_iMax;
}

void TFDynamics::setIMax(int iMax)
{
	m_iMax = iMax;
}

const QString & TFDynamics::fileName()
{
	return m_fileName;
}
