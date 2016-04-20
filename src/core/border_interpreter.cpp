#include "border_interpreter.h"
#include "argument.h"
#include "border.h"

Border_interpreter::Border_interpreter()
{
	this->argument_for_calc = ArgumentForCalc();
}

Border_interpreter::Border_interpreter(const QVector<Border> & Borders)
{
	get_maxs_and_mins(Borders);
}

ArgumentForCalc Border_interpreter::get_argument_for_calc()
{
	return argument_for_calc;
}

void Border_interpreter::get_maxs_and_mins(const QVector<Border>& Borders)
{
	double x_length, y_length;
	x_max = x_min = Borders[0].first().x();
	y_max = y_min = Borders[0].first().y();

	for(Border b: Borders) {
		if(x_max < b.first().x())
			x_max = b.first().x();
		if(x_max < b.second().x())
			x_max = b.first().x();

		if(y_max < b.first().y())
			x_max = b.first().y();
		if(y_max < b.second().y())
			x_max = b.first().y();

		if(x_min > b.first().x())
			x_min = b.first().x();
		if(x_min > b.second().x())
			x_min = b.first().x();

		if(y_min > b.first().y())
			y_min = b.first().y();
		if(y_min > b.second().y())
			y_min = b.first().y();
	}

	x_length = x_max - x_min;
	y_length = y_max - y_min;

	x_max += 0.05 * x_length;
	y_max += 0.05 * y_length;
	x_min -= 0.05 * x_length;
	y_min -= 0.05 * y_length;

}

