#include "plottingwidget.h"
#include "qcustomplot.h"
PlottingWidget::PlottingWidget(QMdiArea * parent) : QMdiSubWindow(parent)
{
	resize(500, 500);
	createCentral();
	createPlot();
	createControls();

	loop = new QTimer(this);
	connect(loop, &QTimer::timeout, this, [=](){
		readNextLayer();
		drawCurrentLayer();
	});
	m_tStep = 1;
}

PlottingWidget::~PlottingWidget()
{
	if (file.isOpen()) {
		file.close();
		file.remove();
	}
}

void PlottingWidget::setData(const TFDynamics& data)
{
	m_data = data;

	m_iMax = m_data.iMax();
	m_jMax = m_data.jMax();
	m_tMax = m_data.tMax();

	if (file.isOpen()) {
		file.close();
		file.remove();
	}

	currentField = TemperatureField(m_iMax, m_jMax);

	colorMap->data()->setRange(QCPRange(0, m_data.xStep() * m_iMax),
							   QCPRange(0, m_data.yStep() * m_jMax));

	colorMap->data()->setSize(m_iMax, m_jMax);

	m_currentIndex = 0;

	m_tStep = m_data.tStep();

	int xSize = static_cast<int>(m_iMax * m_data.xStep());
	int ySize = static_cast<int>(m_jMax * m_data.yStep());
	double aspect = 1.0 * xSize / ySize;
	if (aspect > 1) {
		ySize = 500 / aspect;
		xSize = 500;
	}
	else {
		ySize = 500;
		xSize = 500 * aspect;
	}

	plot->resize(xSize, ySize);
	plot->rescaleAxes();
	resize(plot->width(), plot->height() + play->height() + 10);
	update();
	plot->replot();
}

void PlottingWidget::startDrawing()
{
	file.setFileName(m_data.fileName());
	file.open(QIODevice::ReadOnly);

	str.setDevice(&file);
	str.setFloatingPointPrecision(QDataStream::SinglePrecision);

	loop->stop();
	int dt = static_cast<int>(10000.0 / m_tMax);
	if (dt == 0) {
		dt = 1;
	}

	loop->start(dt);
}

void PlottingWidget::resumeDrawing()
{
	loop->stop();
	int dt = static_cast<int>(10000.0 / m_tMax);
	if (dt == 0) {
		dt = 1;
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
	setCurrentIndex(0);
	file.close();
}

void PlottingWidget::readNextLayer()
{
	if (!str.atEnd()) {
		setCurrentIndex(currentIndex() + 1);
		str >> currentField;
	}
	else {
		loop->stop();
	}
}


void PlottingWidget::drawCurrentLayer()
{
	double x, y, z;

	for (int i = 0; i < m_iMax; ++i)
	{
	  for (int j = 0; j < m_jMax; ++j)
	  {
		colorMap->data()->cellToCoord(i, j, &x, &y);
		z = currentField(i, j);
		colorMap->data()->setCell(i, j, z);
	  }
	}
	colorMap->rescaleDataRange();

	plot->replot();
}

void PlottingWidget::createCentral()
{
	main = new QVBoxLayout();
	setLayout(main);
	down = new QHBoxLayout();

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
	plot->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

	layout()->addWidget(plot);
}

void PlottingWidget::createControls()
{
	lcdTime = new QLCDNumber(this);
	lcdTime->setSegmentStyle(QLCDNumber::Flat);
	lcdTime->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	play = new QPushButton("Play", this);
	pause = new QPushButton("Pause", this);
	stop = new QPushButton("Stop", this);

	down->addWidget(play);
	down->addWidget(pause);
	down->addWidget(stop);
	down->addWidget(lcdTime, Qt::AlignRight);


	connect(play, &QPushButton::clicked, this, [=](){
		if (currentIndex() == 0 || currentIndex() == m_tMax) {
			startDrawing();
		}
		else {
			resumeDrawing();
		}
	});

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
	lcdTime->display(currentIndex * m_tStep);
}
