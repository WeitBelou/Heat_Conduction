#ifndef TFDYNAMICS_H
#define TFDYNAMICS_H
#include "layer.h"

#include <QVector>

class TFDynamics
{
public:
	TFDynamics();
	explicit TFDynamics(float tStep);
	TFDynamics(float tStep, float xStep, float yStep);
	TFDynamics(float tStep, float xStep, float yStep,
			   float tMax, int iMax, int jMax);
	TFDynamics(const TFDynamics& other);
	~TFDynamics();

	TFDynamics & operator =(const TFDynamics & other);

	float tStep() const;
	void setTStep(float tStep);

	float xStep() const;
	void setXStep(float xStep);

	float yStep() const;
	void setYStep(float yStep);

	const QString & fileName();

	int iMax() const;
	void setIMax(int iMax);

	int jMax() const;
	void setJMax(int jMax);

	float tMax() const;
	void setTMax(float tMax);

private:
	void createFileStream();

	QString m_fileName;

	double m_tStep;
	double m_xStep;
	double m_yStep;

	int m_iMax;
	int m_jMax;
	float m_tMax;
};

#endif // TFDYNAMICS_H
