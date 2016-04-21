//Основная цель данного класса - создание класса ArgumentForCalc c
//переменными Layer zeroLayer, BoolNet idNet, double xStep и double yStep,
//заполненными в соответсвии с интерпетацией данных, полученных из
//QVector<Border> Borders; все остальные переменные инициализируются нулями.

#ifndef BORDER_INTERPRETER_H
#define BORDER_INTERPRETER_H

#include "argument.h"
#include "border.h"
#include <limits>


class Border_interpreter
{
	public:
	Border_interpreter();
	Border_interpreter(const QVector<Border> & Borders,
					   const int max_number_of_points_per_dimension = 10000,
					   const int min_number_of_points_per_dimension = 100,
					   const int min_number_of_points_between_close_borders = 10);
	ArgumentForCalc get_argument_for_calc();



private:
	ArgumentForCalc argument_for_calc;
	double x_max, x_min, y_max, y_min;
	double length, height, x_min_dist, y_min_dist;
	void find_area_parameters(const QVector<Border>& Borders,
						const int& max_number_of_points_per_dimension,
						const int& min_number_of_points_per_dimension,
						const int& min_number_of_points_between_close_borders);
	void check_min_dist(const QVector<Border>& Borders, const int& i, const int& j);
	void make_grid();
	void draw_borders(const QVector<Border>& Borders);
	Grid_point p_to_gp(const Point& p);
	Grid_point move_point(Grid_point& p1, const Grid_point& p2);
	void put_point(const Grid_point& p, const double& u);
	void put_point(const Grid_point& p);
	void paint_blank_area(const Grid_point& p);
};

#endif // BORDER_INTERPRETER_H
