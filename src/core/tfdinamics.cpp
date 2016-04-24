#include "tfdinamics.h"


TFDinamics::TFDinamics()
{
	m_temperatureFields = QVector<TemperatureField>(1, TemperatureField());

	m_xStep = 1;
	m_yStep = 1;
	m_tStep = 1;
}

TFDinamics::TFDinamics(const QVector<TemperatureField>& temperatureFields)
{
	m_temperatureFields = temperatureFields;

	m_tStep = 1;
	m_xStep = 1;
	m_yStep = 1;
}

TFDinamics::TFDinamics(const QVector<TemperatureField>& temperatureFields, TFDinamics::tStep)
{
	m_temperatureFields = temperatureFields;

	m_tStep = tStep;
	m_xStep = 1;
	m_yStep = 1;
}

TFDinamics::TFDinamics(const QVector<TemperatureField>& temperatureFields, tStep, xStep, yStep)
{
	m_temperatureFields = temperatureFields;

	m_tStep = tStep;
	m_xStep = xStep;
	m_yStep = yStep;
}


TFDinamics::TFDinamics(const TFDinamics& other)
{
	m_temperatureFields = other.temperatureFields();

	m_tStep = other.tStep();
	m_xStep = other.xStep();
	m_yStep = other.yStep();
}

const TFDinamics TFDinamics::operator =(const TFDinamics& other)
{
	setTemperatureFields(other.temperatureFields());
	setTStep(other.tStep());
	setXStep(other.xStep());
	setYStep(other.yStep());

	return *this;
}

QVector<TemperatureField> TFDinamics::temperatureFields() const
{
	return m_temperatureFields;
}

void TFDinamics::setTemperatureFields(const QVector<TemperatureField>& temperatureFields)
{
	m_temperatureFields = temperatureFields;
}

double TFDinamics::tStep() const
{
	return m_tStep;
}

void TFDinamics::setTStep(double tStep)
{
	m_tStep = tStep;
}

double TFDinamics::xStep() const
{
	return m_xStep;
}

void TFDinamics::setXStep(double xStep)
{
	m_xStep = xStep;
}

double TFDinamics::yStep() const
{
	return m_yStep;
}

void TFDinamics::setYStep(double yStep)
{
	m_yStep = yStep;
}
