#ifndef CALCULATE_DIALOG_H
#define CALCULATE_DIALOG_H

#include <QtWidgets>
#include "core/border_interpreter.h"
#include "core/material.h"
#include "core/problem.h"

class CalculateDialog : public QDialog
{
	Q_OBJECT
public:
	explicit CalculateDialog(QWidget * parent = 0);
	CalculateDialog(const QVector<QVector<Border> > & value,QWidget * parent = 0);


public slots:
	void setInputData(const QVector<QVector<Border> > & value);

signals:
	void calculated(const TFDynamics & dynamics);

private slots:
	void calculate();
	void cancel();

	void addLogMessage(const QString & s);

	void setTMax(double value);
	void setTStep(double value);

private:
	void createCentral();
	void createMaterials();
	void createInput();
	void createButtons();
	void createProgress();

	QVector<Border> inputData;

	QVBoxLayout * mainLayout;
	QFormLayout * inputLayout;
	QHBoxLayout * buttons;

	QLabel * tMaxLabel;
	QDoubleSpinBox * tMaxEdit;

	QLabel * tStepLabel;
	QDoubleSpinBox * tStepEdit;

	QPushButton * calculateButton;
	QPushButton * cancelButton;

	QProgressBar * progress;

	QTextBrowser * log;

	QComboBox * materialChooser;

	double tMax;
	double tStep;
};

#endif // CALCULATE_DIALOG_H
