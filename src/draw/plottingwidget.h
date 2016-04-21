#ifndef PLOTTINGWIDGET_H
#define PLOTTINGWIDGET_H

#include <QtWidgets>
#include "qcustomplot.h"
#include "../core/layer.h"
#include "../core/argument.h"

class PlottingWidget : public QWidget
{
	Q_OBJECT
public:
	explicit PlottingWidget(QWidget *parent = 0);

public slots:
	void setData(const ArgumentForDraw &data);

private slots:
	void startDrawing();
	void pauseDrawing();
	void stopDrawing();
	void drawCurrentLayer();
	void setCurrentIndex(int currentIndex);
	void setSpeed(double d = 1);

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

	QSlider * slider;
	QPushButton * play;
	QPushButton * pause;
	QPushButton * stop;
	QDoubleSpinBox * speed;

	ArgumentForDraw m_data;
	int m_currentIndex;

	QTimer * loop;
	double m_speed;
};

#endif // PLOTTINGWIDGET_H
