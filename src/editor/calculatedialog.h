#ifndef CALCULATEDIALOG_H
#define CALCULATEDIALOG_H

#include <QtWidgets>
#include "core/border_interpreter.h"
#include "core/material.h"
#include "core/problem.h"

class CalculateDialog : public QDialog
{
	Q_OBJECT
public:
	CalculateDialog(QWidget * parent = 0);
	CalculateDialog(const QVector<QVector<Border> > & value,QWidget * parent = 0);


public slots:
	void setInputData(const QVector<QVector<Border> > & value);

signals:
	void calculated(const TFDynamics dynamics);

private slots:
	void calculate();
	void cancel();

	void setTMax(double value);
	void setTStep(double value);

private:
	QVector<Border> inputData;

	QLabel * tMaxLabel;
	QDoubleSpinBox * tMaxEdit;

	QLabel * tStepLabel;
	QDoubleSpinBox * tStepEdit;

	QPushButton * calculateButton;
	QPushButton * cancelButton;

	QProgressBar * progress;

	double tMax;
	double tStep;
};

#endif // CALCULATEDIALOG_H
