#include "calculatedialog.h"

CalculateDialog::CalculateDialog(QWidget * parent):
	QDialog(parent)
{
	tMaxLabel = new QLabel("tMax", this);
	tMaxEdit = new QDoubleSpinBox(this);
	tMaxEdit->setMinimum(0);
	tMaxEdit->setMaximum(1e6);
	connect(tMaxEdit, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			this, &CalculateDialog::setTMax);
	tMaxEdit->setValue(10);

	tStepLabel = new QLabel("tStep", this);
	tStepEdit = new QDoubleSpinBox(this);
	tStepEdit->setMinimum(0);
	tStepEdit->setMaximum(100);
	connect(tStepEdit, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			this, &CalculateDialog::setTStep);
	tStepEdit->setValue(1);

	calculateButton = new QPushButton(tr("Calculate"), this);
	cancelButton = new QPushButton(tr("Cancel"), this);

	progress = new QProgressBar(this);

	QVBoxLayout * mainLayout = new QVBoxLayout(this);

	QFormLayout * inputLayout = new QFormLayout;
	mainLayout->addItem(inputLayout);
	inputLayout->addRow(tMaxLabel, tMaxEdit);
	inputLayout->addRow(tStepLabel, tStepEdit);

	QHBoxLayout * buttons = new QHBoxLayout;
	mainLayout->addItem(buttons);
	buttons->addStretch(1);
	buttons->addWidget(calculateButton);
	buttons->addWidget(cancelButton);

	mainLayout->addWidget(progress);

	connect(calculateButton, &QPushButton::clicked, this, &CalculateDialog::calculate);
	connect(cancelButton, &QPushButton::clicked, this, &CalculateDialog::cancel);
}

CalculateDialog::CalculateDialog(const QVector<QVector<Border> > & value, QWidget * parent):
	CalculateDialog(parent)
{
	setInputData(value);
}

void CalculateDialog::calculate()
{
	BorderInterpreter borderInterpreter(inputData, 100);
	TFGeometry geom = borderInterpreter.workingArea();

	Material m;

	Problem * p =  new Problem(m, geom, tMax, tStep, this);

	connect(p, &Problem::oneLayerCalcSignal, [=](double percent){
		qApp->processEvents();
		progress->setValue(100 * percent);
	});

	TFDynamics tmp = p->solve();
	emit calculated(tmp);

	accept();
}

void CalculateDialog::cancel()
{
	reject();
}

void CalculateDialog::setTStep(double value)
{
	tStep = value;
}

void CalculateDialog::setTMax(double value)
{
	tMax = value;
}

void CalculateDialog::setInputData(const QVector<QVector<Border> > & value)
{
	inputData.clear();

	for (QVector<Border> b: value) {
		for (Border bor: b) {
			inputData.push_back(bor);
		}
	}
}

