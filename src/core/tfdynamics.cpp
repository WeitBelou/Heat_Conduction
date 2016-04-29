#include "tfdynamics.h"


TFDynamics::TFDynamics()
{
	m_temperatureFields = QVector<TemperatureField>(1, TemperatureField());

	m_xStep = 1;
	m_yStep = 1;
	m_tStep = 1;
}

TFDynamics::TFDynamics(const QVector<TemperatureField>& temperatureFields)
{
	m_temperatureFields = temperatureFields;

	m_tStep = 1;
	m_xStep = 1;
	m_yStep = 1;
}

TFDynamics::TFDynamics(const QVector<TemperatureField>& temperatureFields, double tStep)
{
	m_temperatureFields = temperatureFields;

	m_tStep = tStep;
	m_xStep = 1;
	m_yStep = 1;
}

TFDynamics::TFDynamics(const QVector<TemperatureField>& temperatureFields,
					   double tStep, double xStep, double yStep)
{
	m_temperatureFields = temperatureFields;

	m_tStep = tStep;
	m_xStep = xStep;
	m_yStep = yStep;
}


TFDynamics::TFDynamics(const TFDynamics& other)
{
	m_temperatureFields = other.temperatureFields();

	m_tStep = other.tStep();
	m_xStep = other.xStep();
	m_yStep = other.yStep();
}

TFDynamics & TFDynamics::operator =(const TFDynamics& other)
{
	m_temperatureFields = other.temperatureFields();
	setTStep(other.tStep());
	setXStep(other.xStep());
	setYStep(other.yStep());

	return *this;
}

const TemperatureField TFDynamics::operator [](int i) const
{
	return m_temperatureFields[i];
}

TemperatureField &TFDynamics::operator [](int i)
{
	return m_temperatureFields[i];
}

void TFDynamics::push_back(const TemperatureField & field)
{
	m_temperatureFields.push_back(field);
}

const QVector<TemperatureField> & TFDynamics::temperatureFields() const
{
	return m_temperatureFields;
}

double TFDynamics::tStep() const
{
	return m_tStep;
}

void TFDynamics::setTStep(double tStep)
{
	m_tStep = tStep;
}

double TFDynamics::xStep() const
{
	return m_xStep;
}

void TFDynamics::setXStep(double xStep)
{
	m_xStep = xStep;
}

double TFDynamics::yStep() const
{
	return m_yStep;
}

void TFDynamics::setYStep(double yStep)
{
	m_yStep = yStep;
}
