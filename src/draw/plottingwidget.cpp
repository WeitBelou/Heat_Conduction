#include "plottingwidget.h"

PlottingWidget::PlottingWidget(QWidget *parent) : QWidget(parent)
{
	setMinimumSize(500, 500);

	createCentral();
	createPlot();
	createControls();

	loop = new QTimer(this);
	connect(loop, &QTimer::timeout, this,
			[this](){slider->setValue(this->currentIndex() + 1);});
	setCurrentIndex(0);
	m_tStep = 1;

}

void PlottingWidget::setData(const TFDynamics& data)
{
	m_data = data;

	m_iMax = m_data.temperatureFields()[0].iMax();
	m_jMax = m_data.temperatureFields()[0].jMax();
	m_tMax = m_data.temperatureFields().size();

	double xSize = m_iMax * m_data.xStep();
	double ySize = m_jMax * m_data.yStep();
	double iMax = m_iMax;
	double jMax = m_jMax;

	if (xSize > ySize) {
		jMax = static_cast<int>(iMax * (xSize / ySize));
		ySize = xSize;
	}
	else {
		iMax = static_cast<int>(jMax * (ySize / xSize));
		xSize = ySize;
	}

	colorMap->data()->setRange(QCPRange(0, xSize),
							   QCPRange(0, ySize));

	colorMap->data()->setSize(iMax, jMax);

	slider->setMaximum(m_data.temperatureFields().size() - 1);
	slider->setValue(0);

	m_tStep = 10.0 / m_tMax;

	plot->rescaleAxes();
}

void PlottingWidget::startDrawing()
{
	loop->stop();
	int dt = static_cast<int>(m_tStep * 1000);
	if (dt == 0) {
		dt = 1;
	}

	if (currentIndex() < m_tMax - 1) {
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
	double x, y, z;

	double xSize = m_iMax * m_data.xStep();
	double ySize = m_jMax * m_data.yStep();
	double iMax = m_iMax;
	double jMax = m_jMax;

	if (xSize > ySize) {
		jMax = static_cast<int>(iMax * (xSize / ySize));
	}
	else {
		iMax = static_cast<int>(jMax * (ySize / xSize));
	}

	for (int i = 0; i < iMax; ++i)
	{
	  for (int j = 0; j < jMax; ++j)
	  {
		colorMap->data()->cellToCoord(i, j, &x, &y);
		if (i > m_iMax - 1 || j > m_jMax - 1 ) {
			z = 0;
		}
		else{
			z = m_data.temperatureFields()[currentIndex()](i, j);
		}
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

//	plot->rescaleAxes();

	layout()->addWidget(plot);
}

void PlottingWidget::createControls()
{
	slider = new QSlider(Qt::Horizontal, this);
	slider->setMinimum(0);
	slider->setMaximum(1);
	slider->setValue(0);

	play = new QPushButton("Play", this);
	pause = new QPushButton("Pause", this);
	stop = new QPushButton("Stop", this);

	down->addWidget(play);
	down->addWidget(pause);
	down->addWidget(stop);
	down->addWidget(slider);


	connect(play, &QPushButton::clicked, this, &PlottingWidget::startDrawing);
	connect(pause, &QPushButton::clicked, this, &PlottingWidget::pauseDrawing);
	connect(stop, &QPushButton::clicked, this, &PlottingWidget::stopDrawing);
	connect(slider, &QSlider::valueChanged, this, &PlottingWidget::setCurrentIndex);
	connect(slider, &QSlider::valueChanged, this, &PlottingWidget::drawCurrentLayer);
}

int PlottingWidget::currentIndex() const
{
	return m_currentIndex;
}

void PlottingWidget::setCurrentIndex(int currentIndex)
{
	m_currentIndex = currentIndex;
}
