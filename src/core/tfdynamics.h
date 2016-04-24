#ifndef TFDYNAMICS_H
#define TFDYNAMICS_H
#include "layer.h"
#include <QVector>

class TFDynamics
{
public:
	TFDynamics();
	TFDynamics(const QVector<TemperatureField>& temperatureFields);
	TFDynamics(const QVector<TemperatureField>& temperatureFields, double tStep);

	TFDynamics(const QVector<TemperatureField>& temperatureFields,
			  double  tStep, double  xStep, double  yStep);
	TFDynamics(const TFDynamics& other);

	const TFDynamics operator =(const TFDynamics& other);

	QVector<TemperatureField> temperatureFields() const;
	void setTemperatureFields(const QVector<TemperatureField>& temperatureFields);

	double tStep() const;
	void setTStep(double tStep);

	double xStep() const;
	void setXStep(double xStep);

	double yStep() const;
	void setYStep(double yStep);

private:
	QVector<TemperatureField> m_temperatureFields;

	double m_tStep;
	double m_xStep;
	double m_yStep;
};





#endif // TFDYNAMICS_H
