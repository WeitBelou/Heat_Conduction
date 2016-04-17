#include "plottingwidget.h"

PlottingWidget::PlottingWidget(QWidget *parent) : QWidget(parent)
{
	l = new QHBoxLayout(this);
	plot = new QCustomPlot(this);
	setLayout(l);
	layout()->addWidget(plot);

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
}

void PlottingWidget::setData(const QVector<Layer> &data)
{
	m_data = data;
}

void PlottingWidget::replot()
{
	Layer l(100, 100);

	int nx = l.getImax();
	int ny = l.getJmax();

	for (int i = 0; i < nx; ++i) {
		for (int j = 0; j < ny; ++j) {
			if (i < j) {
				l(i, j) = -5;
			}
			else {
				l(i, j) = 5;
			}
		}
	}

	///Генерируем какие-нибудь данные по теплопроводности

	colorMap->data()->setSize(nx, ny);
	colorMap->data()->setRange(QCPRange(-4, 4), QCPRange(-4, 4));
	double x, y, z;

	for (int xIndex = 0; xIndex < nx; ++xIndex)
	{
	  for (int yIndex = 0; yIndex < ny; ++yIndex)
	  {
		colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
		z = l(xIndex, yIndex);
		colorMap->data()->setCell(xIndex, yIndex, z);
	  }
	}
	///
	colorMap->rescaleDataRange();
	plot->rescaleAxes();
	plot->replot();
}

