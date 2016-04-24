#ifndef TFDINAMICS_H
#define TFDINAMICS_H
#include "layer.h"
#include <QVector>

class TFDinamics
{
public:
	TFDinamics();
	TFDinamics(const QVector<Layer>& temperatureFields);
	TFDinamics(const QVector<Layer>& temperatureFields, tStep);
	TFDinamics(const QVector<Layer>& temperatureFields,
			   tStep, xStep, yStep);
	TFDinamics(const TFDinamics& other);

	const TFDinamics operator =(const TFDinamics& other);

	QVector<Layer> temperatureFields() const;
	void setTemperatureFields(const QVector<Layer>& temperatureFields);

	double tStep() const;
	void setTStep(double tStep);

	double xStep() const;
	void setXStep(double xStep);

	double yStep() const;
	void setYStep(double yStep);

private:
	QVector<Layer> m_temperatureFields;

	double m_tStep;
	double m_xStep;
	double m_yStep;
};





#endif // TFDINAMICS_H
