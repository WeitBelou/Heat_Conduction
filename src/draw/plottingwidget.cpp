#include "plottingwidget.h"

PlottingWidget::PlottingWidget(QWidget *parent) : QWidget(parent)
{
	l = new QHBoxLayout(this);
	plot = new QCustomPlot(this);
	setLayout(l);
	layout()->addWidget(plot);

	loop = new QTimer(this);
	connect(loop, &QTimer::timeout, this, &PlottingWidget::drawCurrentLayer);

	configurePlot();
}

void PlottingWidget::setData(const QVector<Layer> &data)
{
	m_data = data;
}

void PlottingWidget::replot()
{
	loop->start(100);
	setCurrentIndex(0);
	drawCurrentLayer();
}

void PlottingWidget::drawCurrentLayer()
{
	int nx = m_data[currentIndex()].getImax();
	int ny = m_data[currentIndex()].getJmax();

	colorMap->data()->setSize(nx, ny);
	colorMap->data()->setRange(QCPRange(-4, 4), QCPRange(-4, 4));
	double x, y, z;

	for (int xIndex = 0; xIndex < nx; ++xIndex)
	{
	  for (int yIndex = 0; yIndex < ny; ++yIndex)
	  {
		colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
		z = m_data[currentIndex()](xIndex, yIndex);
		colorMap->data()->setCell(xIndex, yIndex, z);
	  }
	}
	///
	colorMap->rescaleDataRange();
	plot->rescaleAxes();
	plot->replot();

	if (currentIndex() < m_data.size() - 1) {
		setCurrentIndex(currentIndex() + 1);
	}
}

void PlottingWidget::configurePlot()
{
	// configure axis rect:
	plot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
	plot->axisRect()->setupFullAxesBox(true);
	plot->xAxis->setLabel("x");
	plot->yAxis->setLabel("y");

	// set up the QCPColorMap:
	colorMap = new QCPColorMap(plot->xAxis, plot->yAxis);
	plot->addPlottable(colorMap);

	colorScale = new QCPColorScale(plot);
	plot->plotLayout()->addElement(0, 1, colorScale);
	colorScale->setType(QCPAxis::atRight);
	colorMap->setColorScale(colorScale);

	colorMap->setGradient(QCPColorGradient::gpPolar);
	colorMap->rescaleDataRange();

	marginGroup = new QCPMarginGroup(plot);
	plot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
	colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

	plot->rescaleAxes();

	setCurrentIndex(0);
}

int PlottingWidget::currentIndex() const
{
	return m_currentIndex;
}

void PlottingWidget::setCurrentIndex(const int &currentIndex)
{
	m_currentIndex = currentIndex;
}

