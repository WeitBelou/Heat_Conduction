#ifndef PLOTTINGWIDGET_H
#define PLOTTINGWIDGET_H

#include <QtWidgets>
#include "qcustomplot.h"
#include "core/layer.h"
#include "core/tfdynamics.h"

class PlottingWidget : public QWidget
{
	Q_OBJECT
public:
	explicit PlottingWidget(QWidget *parent = 0);

public slots:
	void setData(const TFDynamics &data);
	void setDataFromFile(const QFile & file);

private slots:
	void startDrawing();
	void pauseDrawing();
	void stopDrawing();
	void drawCurrentLayer();
	void setCurrentIndex(int currentIndex);

private:
	void createCentral();
	void createPlot();
	void createControls();

	int currentIndex() const;

	QCustomPlot * plot;
	QCPColorMap * colorMap;
	QCPColorScale * colorScale;
	QCPMarginGroup * marginGroup;

	QVBoxLayout * main;
	QHBoxLayout * down;

	QLCDNumber * lcdTime;
	QSlider * slider;
	QPushButton * play;
	QPushButton * pause;
	QPushButton * stop;

	TFDynamics m_data;
	int m_iMax;
	int m_jMax;
	int m_tMax;

	int m_currentIndex;

	QTimer * loop;
	double m_tStep;
};

#endif // PLOTTINGWIDGET_H
