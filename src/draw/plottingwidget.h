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
	~PlottingWidget();

public slots:
	void setData(const TFDynamics &data);

private slots:
	void startDrawing();
	void resumeDrawing();
	void pauseDrawing();
	void stopDrawing();
	void readNextLayer();
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
	QPushButton * play;
	QPushButton * pause;
	QPushButton * stop;

	TFDynamics m_data;
	TemperatureField currentField;
	QFile file;
	QDataStream str;


	int m_iMax;
	int m_jMax;
	int m_tMax;

	int m_currentIndex;

	QTimer * loop;
	double m_tStep;
};

#endif // PLOTTINGWIDGET_H
