#include "plottingwidget.h"

PlottingWidget::PlottingWidget(QWidget *parent) : QWidget(parent),
	m_data()
{
	setMinimumSize(400, 400);
	createCentral();
	createPlot();
	createControls();

	loop = new QTimer(this);
	connect(loop, &QTimer::timeout, this,
			[this](){slider->setValue(this->currentIndex() + 1);});
	m_tStep = 1;

}

void PlottingWidget::setData(const TFDynamics& data)
{
	m_data = data;

	m_iMax = m_data.temperatureFields()[0].iMax();
	m_jMax = m_data.temperatureFields()[0].jMax();
	m_tMax = m_data.temperatureFields().size() - 1;

	colorMap->data()->setRange(QCPRange(0, m_data.xStep() * m_iMax),
							   QCPRange(0, m_data.yStep() * m_jMax));

	colorMap->data()->setSize(m_iMax, m_jMax);

	slider->setMaximum(m_tMax);
	slider->setValue(0);

	m_tStep = m_data.tStep();

	plot->rescaleAxes();
}

void PlottingWidget::startDrawing()
{
	if (m_data.temperatureFields().isEmpty()) {
		return;
	}

	loop->stop();
	int dt = static_cast<int>(10000.0 / m_tMax);
	if (dt == 0) {
		dt = 1;
	}

	if (currentIndex() < m_tMax) {
		slider->setValue(currentIndex() + 1);
		loop->stop();
	}
	loop->start(dt);
}

void PlottingWidget::pauseDrawing()
{
	loop->stop();
}

void PlottingWidget::stopDrawing()
{
	loop->stop();
	slider->setValue(0);
}


void PlottingWidget::drawCurrentLayer()
{
	if (m_data.temperatureFields().isEmpty()) {
		return;
	}

	double x, y, z;

	for (int i = 0; i < m_iMax; ++i)
	{
	  for (int j = 0; j < m_jMax; ++j)
	  {
		colorMap->data()->cellToCoord(i, j, &x, &y);
		z = m_data.temperatureFields()[currentIndex()](i, j);
		colorMap->data()->setCell(i, j, z);
	  }
	}
	colorMap->rescaleDataRange();

	plot->replot();
}

void PlottingWidget::createCentral()
{
	main = new QVBoxLayout(this);
	down = new QHBoxLayout();

	setLayout(main);
	layout()->addItem(down);
}

void PlottingWidget::createPlot()
{
	plot = new QCustomPlot(this);

	plot->axisRect()->setupFullAxesBox(true);

	colorMap = new QCPColorMap(plot->xAxis, plot->yAxis);
	plot->addPlottable(colorMap);

	colorScale = new QCPColorScale(plot);
	plot->plotLayout()->addElement(0, 1, colorScale);
	colorScale->setType(QCPAxis::atRight);
	colorMap->setColorScale(colorScale);

	colorMap->setGradient(QCPColorGradient::gpThermal);
	colorMap->rescaleDataRange();

	marginGroup = new QCPMarginGroup(plot);
	plot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
	colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

	layout()->addWidget(plot);
}

void PlottingWidget::createControls()
{
	slider = new QSlider(Qt::Horizontal, this);
	slider->setMinimum(0);
	slider->setMaximum(1);
	slider->setValue(0);

	lcdTime = new QLCDNumber(this);
	lcdTime->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);

	connect(slider, &QSlider::valueChanged, this, &PlottingWidget::setCurrentIndex);
	connect(slider, &QSlider::valueChanged, this, &PlottingWidget::drawCurrentLayer);
	connect(slider, &QSlider::valueChanged, lcdTime, [=](int i) {
		lcdTime->display(m_tStep * i);
	});

	play = new QPushButton("Play", this);
	pause = new QPushButton("Pause", this);
	stop = new QPushButton("Stop", this);

	down->addWidget(play);
	down->addWidget(pause);
	down->addWidget(stop);
	down->addWidget(slider);
	down->addWidget(lcdTime, Qt::AlignRight);


	connect(play, &QPushButton::clicked, this, &PlottingWidget::startDrawing);
	connect(pause, &QPushButton::clicked, this, &PlottingWidget::pauseDrawing);
	connect(stop, &QPushButton::clicked, this, &PlottingWidget::stopDrawing);
}

int PlottingWidget::currentIndex() const
{
	return m_currentIndex;
}

void PlottingWidget::setCurrentIndex(int currentIndex)
{
	m_currentIndex = currentIndex;
}
