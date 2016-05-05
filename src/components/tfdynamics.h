#ifndef TFDYNAMICS_H
#define TFDYNAMICS_H
#include "layer.h"

#include <QVector>

class TFDynamics
{
public:
	TFDynamics();
	explicit TFDynamics(double tStep);
	TFDynamics(double tStep, double xStep, double yStep);
	TFDynamics(double tStep, double xStep, double yStep,
			   int tMax, int iMax, int jMax);
	TFDynamics(const TFDynamics& other);
	~TFDynamics();

	TFDynamics & operator =(const TFDynamics & other);

	double tStep() const;
	void setTStep(double tStep);

	double xStep() const;
	void setXStep(double xStep);

	double yStep() const;
	void setYStep(double yStep);

	const QString & fileName();

	int iMax() const;
	void setIMax(int iMax);

	int jMax() const;
	void setJMax(int jMax);

	int tMax() const;
	void setTMax(int tMax);

private:
	void createFileStream();

	QString m_fileName;

	double m_tStep;
	double m_xStep;
	double m_yStep;

	int m_iMax;
	int m_jMax;
	int m_tMax;
};

#endif // TFDYNAMICS_H
