//Основная цель данного класса - создание класса ArgumentForCalc c
//переменными Layer zeroLayer, BoolNet idNet, double xStep и double yStep,
//заполненными в соответсвии с интерпетацией данных, полученных из
//QVector<Border> Borders; все остальные переменные инициализируются нулями.

#ifndef BORDER_INTERPRETER_H
#define BORDER_INTERPRETER_H

#include "argument.h"
#include "border.h"


class Border_interpreter
{
	public:
	Border_interpreter();
	Border_interpreter(const QVector<Border> & Borders);
	ArgumentForCalc get_argument_for_calc();


private:
	ArgumentForCalc argument_for_calc;
	double x_max, x_min, y_max, y_min;
	double x_length, y_length;
	void get_maxs_and_mins(const QVector<Border> & Borders);
};

#endif // BORDER_INTERPRETER_H
