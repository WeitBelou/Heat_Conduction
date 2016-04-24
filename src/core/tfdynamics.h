#ifndef TFDINAMICS_H
#define TFDINAMICS_H
#include "layer.h"
#include <QVector>

class TFDinamics
{
public:
	TFDinamics();
	TFDinamics(const QVector<TemperatureField>& temperatureFields);
	TFDinamics(const QVector<TemperatureField>& temperatureFields, tStep);
	TFDinamics(const QVector<TemperatureField>& temperatureFields,
			   tStep, xStep, yStep);
	TFDinamics(const TFDinamics& other);

	const TFDinamics operator =(const TFDinamics& other);

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





#endif // TFDINAMICS_H
