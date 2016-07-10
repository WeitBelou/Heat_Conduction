#ifndef CALCULATE_DIALOG_H
#define CALCULATE_DIALOG_H

#include <QtWidgets>
#include <libheat/components/border.h>

#include "libheat/border_interpreter/border_interpreter.h"
#include "libheat/problem/problem.h"

class Material;

class CalculatingDialog : public QDialog
{
	Q_OBJECT
public:
	explicit CalculatingDialog(QWidget * parent = 0);
	CalculatingDialog(const QVector<QVector<Border> > & value,QWidget * parent = 0);


public slots:
	void setInputData(const QVector<QVector<Border> > & value);

signals:
	void calculated(const TFDynamics & dynamics);

private slots:
	void calculate();
	void cancel();

	void addLogMessage(const QString & s);

	void setTMax (float value);
	void setTStep (float value);

private:
	void createCentral();
	void createMaterials();
	void createInput();
	void createButtons();
	void createProgress();

	QVector<Border> inputData;
	TFDynamics outputData;

	QVBoxLayout * mainLayout;
	QFormLayout * inputLayout;
	QHBoxLayout * buttons;

	QLabel * tMaxLabel;
	QDoubleSpinBox * tMaxEdit;

	QLabel * tStepLabel;
	QDoubleSpinBox * tStepEdit;

	QPushButton * okButton;
	QPushButton * cancelButton;

	QProgressBar * progress;

	QPlainTextEdit * log;

	QComboBox * materialChooser;

	float tMax;
	float tStep;

	bool isDone;
	bool isCalculating;
};

#endif // CALCULATE_DIALOG_H
