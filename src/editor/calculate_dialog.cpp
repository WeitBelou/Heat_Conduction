#include "calculate_dialog.h"

CalculateDialog::CalculateDialog(QWidget * parent):
	QDialog(parent)
{
	createCentral();
	createMaterials();
	createInput();
	createButtons();
	createProgress();
}

CalculateDialog::CalculateDialog(const QVector<QVector<Border> > & value, QWidget * parent):
	CalculateDialog(parent)
{
	setInputData(value);
}

void CalculateDialog::calculate()
{
	BorderInterpreter *  borderInterpreter = new BorderInterpreter(inputData, 10000);
	connect(borderInterpreter, &BorderInterpreter::logSent,
			this, &CalculateDialog::addLogMessage);

	TFGeometry geom = borderInterpreter->workingArea();
	delete borderInterpreter;

	Material m = materialChooser->itemData(materialChooser->currentIndex()).value<Material>();

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

void CalculateDialog::addLogMessage(const QString & s)
{

}

void CalculateDialog::setTStep(double value)
{
	tStep = value;
}

void CalculateDialog::createCentral()
{
	mainLayout = new QVBoxLayout(this);
}

void CalculateDialog::createMaterials()
{
	materialChooser = new QComboBox(this);
	materialChooser->addItem(QString("Steel"), QVariant::fromValue(Material(7800, 46, 462)));
	materialChooser->addItem(QString("Aluminium"), QVariant::fromValue(Material(2700, 272, 903)));
	materialChooser->addItem(QString("Copper"), QVariant::fromValue(Material(8930, 371, 385)));

	mainLayout->addWidget(materialChooser);
}

void CalculateDialog::createInput()
{
	inputLayout = new QFormLayout;
	mainLayout->addItem(inputLayout);

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

	inputLayout->addRow(tMaxLabel, tMaxEdit);
	inputLayout->addRow(tStepLabel, tStepEdit);
}

void CalculateDialog::createButtons()
{
	buttons = new QHBoxLayout;
	mainLayout->addItem(buttons);

	calculateButton = new QPushButton(tr("Calculate"), this);
	cancelButton = new QPushButton(tr("Cancel"), this);

	buttons->addStretch(1);
	buttons->addWidget(calculateButton);
	buttons->addWidget(cancelButton);

	connect(calculateButton, &QPushButton::clicked, this, &CalculateDialog::calculate);
	connect(cancelButton, &QPushButton::clicked, this, &CalculateDialog::cancel);
}

void CalculateDialog::createProgress()
{
	progress = new QProgressBar(this);

	log = new QTextBrowser(this);

	mainLayout->addWidget(progress);
	mainLayout->addWidget(log);
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

