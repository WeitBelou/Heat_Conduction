#include "calculating_dialog.h"

#include "material.h"
CalculatingDialog::CalculatingDialog(QWidget * parent):
	QDialog(parent)
{
	createCentral();
	createMaterials();
	createInput();
	createButtons();
	createProgress();
}

CalculatingDialog::CalculatingDialog(const QVector<QVector<Border> > & value, QWidget * parent):
	CalculatingDialog(parent)
{
	setInputData(value);
}

void CalculatingDialog::calculate()
{
	okButton->setDisabled(true);

	isCalculating = true;
	BorderInterpreter *  borderInterpreter = new BorderInterpreter(inputData);
	connect(borderInterpreter, &BorderInterpreter::logSent,
			this, &CalculatingDialog::addLogMessage);
	borderInterpreter->solve();

	TFGeometry geom = borderInterpreter->workingArea();
	delete borderInterpreter;

	Material m = materialChooser->itemData(materialChooser->currentIndex()).value<Material>();

	Problem * p =  new Problem(m, geom, tMax, tStep, this);

	connect(p, &Problem::layerCalcDone, [=](double percent){
		qApp->processEvents();
		progress->setValue(100 * percent);
	});

	connect(cancelButton, &QPushButton::clicked, p, &Problem::stopCalc);

	outputData = p->solve();

	isDone = true;
	isCalculating = false;
	okButton->setDisabled(false);
}

void CalculatingDialog::cancel()
{
	if (!isCalculating) {
		reject();
	}
}

void CalculatingDialog::addLogMessage(const QString & s)
{
	log->appendPlainText(QString("%1\n").arg(s));
}

void CalculatingDialog::setTStep(double value)
{
	tStep = value;
}

void CalculatingDialog::createCentral()
{
	mainLayout = new QVBoxLayout(this);
}

void CalculatingDialog::createMaterials()
{
	materialChooser = new QComboBox(this);
	materialChooser->addItem(QString("Steel"), QVariant::fromValue(Material(7800, 46, 462)));
	materialChooser->addItem(QString("Aluminium"), QVariant::fromValue(Material(2700, 272, 903)));
	materialChooser->addItem(QString("Copper"), QVariant::fromValue(Material(8930, 371, 385)));

	mainLayout->addWidget(materialChooser);
}

void CalculatingDialog::createInput()
{
	inputLayout = new QFormLayout;
	mainLayout->addItem(inputLayout);

	tMaxLabel = new QLabel("tMax", this);
	tMaxEdit = new QDoubleSpinBox(this);
	tMaxEdit->setMinimum(0);
	tMaxEdit->setMaximum(1e6);
	connect(tMaxEdit, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			this, &CalculatingDialog::setTMax);
	tMaxEdit->setValue(10);

	tStepLabel = new QLabel("tStep", this);
	tStepEdit = new QDoubleSpinBox(this);
	tStepEdit->setMinimum(0);
	tStepEdit->setMaximum(100);
	connect(tStepEdit, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			this, &CalculatingDialog::setTStep);
	tStepEdit->setValue(1);

	inputLayout->addRow(tMaxLabel, tMaxEdit);
	inputLayout->addRow(tStepLabel, tStepEdit);

	isDone = false;
	isCalculating = false;
}

void CalculatingDialog::createButtons()
{
	buttons = new QHBoxLayout;
	mainLayout->addItem(buttons);

	okButton = new QPushButton(tr("Calculate"), this);
	cancelButton = new QPushButton(tr("Cancel"), this);

	buttons->addStretch(1);
	buttons->addWidget(okButton);
	buttons->addWidget(cancelButton);

	connect(okButton, &QPushButton::clicked, this, [=](){
		if (isDone) {
			emit calculated(outputData);
			accept();
		}
		else
			okButton->setText("Ok");
			calculate();
	});

	connect(cancelButton, &QPushButton::clicked, this, &CalculatingDialog::cancel);
}

void CalculatingDialog::createProgress()
{
	isDone = false;

	progress = new QProgressBar(this);

	log = new QPlainTextEdit(this);
	log->setReadOnly(true);

	mainLayout->addWidget(progress);
	mainLayout->addWidget(log);
}

void CalculatingDialog::setTMax(double value)
{
	tMax = value;
}

void CalculatingDialog::setInputData(const QVector<QVector<Border> > & value)
{
	inputData.clear();

	for (QVector<Border> b: value) {
		for (Border bor: b) {
			inputData.push_back(bor);
		}
	}
}

