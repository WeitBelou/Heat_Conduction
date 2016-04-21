#include "border_interpreter.h"


Border_interpreter::Border_interpreter()
{
	this->argument_for_calc = ArgumentForCalc();
}

Border_interpreter::Border_interpreter(const QVector<Border>& Borders,
					const int max_number_of_points_per_dimension,
					const int min_number_of_points_per_dimension,
					const int min_number_of_points_between_close_borders)
{
	//рассчёт параметров области построения
	find_area_parameters(Borders, max_number_of_points_per_dimension,
						 min_number_of_points_per_dimension,
						 min_number_of_points_between_close_borders);
	//создание сетки
	make_grid();
	draw_borders(Borders);
	paint_blank_area(Grid_point(0, 0));
}



ArgumentForCalc Border_interpreter::get_argument_for_calc()
{
	return argument_for_calc;
}

void Border_interpreter::find_area_parameters(const QVector<Border>& Borders,
					const int& max_number_of_points_per_dimension,
					const int& min_number_of_points_per_dimension,
					const int& min_number_of_points_between_close_borders)
{
	x_max = x_min = Borders[0].first().x();
	y_max = y_min = Borders[0].first().y();
	x_min_dist = y_min_dist = std::numeric_limits<double>::max();


	for(int i = 0, max = Borders.size(); i < max; i++) {
		if(x_max < Borders[i].first().x())
			x_max = Borders[i].first().x();
		if(x_max < Borders[i].second().x())
			x_max = Borders[i].first().x();

		if(y_max < Borders[i].first().y())
			x_max = Borders[i].first().y();
		if(y_max < Borders[i].second().y())
			x_max = Borders[i].first().y();

		if(x_min > Borders[i].first().x())
			x_min = Borders[i].first().x();
		if(x_min > Borders[i].second().x())
			x_min = Borders[i].first().x();

		if(y_min > Borders[i].first().y())
			y_min = Borders[i].first().y();
		if(y_min > Borders[i].second().y())
			y_min = Borders[i].first().y();

		for(int j = i; j < max; j++) {
			check_min_dist(Borders, i, j);
		}
	}

	length = x_max - x_min;
	height = y_max - y_min;

	x_max += 0.05 * length;
	y_max += 0.05 * length;
	x_min -= 0.05 * height;
	y_min -= 0.05 * height;




	//некоторые неочевидные вычисления необходимы для гарантированного
	//наличия пустого простанства между краями области построения и
	//границами тела
	//для x
	if(x_min_dist > length / max_number_of_points_per_dimension) {

		if(x_min_dist < length / (min_number_of_points_per_dimension/
								  min_number_of_points_between_close_borders) ) {
			argument_for_calc.xStep = x_min_dist /
									min_number_of_points_between_close_borders;
		}
		else {
			argument_for_calc.xStep = length / min_number_of_points_per_dimension;
		}
	}
	else {
		argument_for_calc.xStep = length / max_number_of_points_per_dimension;
	}

	x_max += argument_for_calc.xStep;
	x_min -= argument_for_calc.xStep;
	length += 2*argument_for_calc.xStep;
	argument_for_calc.iMax = length / argument_for_calc.xStep;


	//для y
	if(y_min_dist > height / max_number_of_points_per_dimension) {

		if(y_min_dist < height / min_number_of_points_per_dimension) {
			argument_for_calc.yStep = x_min_dist / min_number_of_points_between_close_borders;
		}
		else {
			argument_for_calc.yStep = height / min_number_of_points_per_dimension;
		}
	}
	else {
		argument_for_calc.yStep = height / max_number_of_points_per_dimension;
	}

	y_max += argument_for_calc.yStep;
	y_min -= argument_for_calc.yStep;
	height += 2*argument_for_calc.yStep;
	argument_for_calc.jMax = height / argument_for_calc.yStep;

}

void Border_interpreter::check_min_dist(const QVector<Border>& Borders, const int& i, const int& j)
{
	if(	std::fabs(Borders[i].first().x() - Borders[j].first().x()) < x_min_dist	)
		x_min_dist = std::fabs(Borders[i].first().x() - Borders[j].first().x());

	if(	std::fabs(Borders[i].first().y() - Borders[j].first().y()) < y_min_dist	)
		y_min_dist = std::fabs(Borders[i].first().y() - Borders[j].first().y());
}

void Border_interpreter::make_grid()
{
	argument_for_calc.zeroLayer = Layer(argument_for_calc.iMax, argument_for_calc.jMax);
	argument_for_calc.idNet = BoolNet(argument_for_calc.iMax, argument_for_calc.jMax);

	for(int i = 0; i < argument_for_calc.iMax; i++) {
		for(int j = 0; j < argument_for_calc.jMax; j++)
			argument_for_calc.idNet(i, j) = true;

	}
}

void Border_interpreter::draw_borders(const QVector<Border>& Borders)
{
	Grid_point p1, p2;
	for(Border b: Borders) {
		p1 = p_to_gp(b.first());
		p2 = p_to_gp(b.second());
		put_point(p2, b.u());

		do {
			put_point(p1, b.u());
			move_point(p1, p2);
		}
		while(p1 != p2);
	}
}

Grid_point Border_interpreter::p_to_gp(const Point& p)
{
	return Grid_point(	(p.x() - x_min) / argument_for_calc.xStep,
						(p.y() - y_min) / argument_for_calc.yStep);
}

Grid_point Border_interpreter::move_point(Grid_point& p1, const Grid_point& p2)
{
	if( std::fabs(p2.x() - p1.x()) > std::fabs(p2.y() - p1.y()) ) {
		if( (p2.x() - p1.x()) > 0)
			return Grid_point( p1.x() + 1, p1.y() );
		else
			return Grid_point( p1.x() - 1, p1.y() );
	}
	else
	{
		if( (p2.y() - p1.y()) > 0)
			return Grid_point( p1.x(), p1.y() + 1 );
		else
			return Grid_point( p1.x(), p1.y() - 1 );
	}
}

void Border_interpreter::put_point(const Grid_point& p, const double& u)
{
	argument_for_calc.zeroLayer(p.x(), p.y()) = u;
	argument_for_calc.idNet(p.x(), p.y()) = 0;
}

void Border_interpreter::paint_blank_area(const Grid_point& p)
{
	if( p.x() < 0 && p.x() >= argument_for_calc.iMax && p.y() < 0 && p.y() >= argument_for_calc.jMax)
		return;
	if( argument_for_calc.idNet(p.x(), p.y()) != false)
		return;

	argument_for_calc.idNet( p.x(), p.y()) = false;
	paint_blank_area(Grid_point(p.x() + 1, p.y()));
	paint_blank_area(Grid_point(p.x() - 1, p.y()));
	paint_blank_area(Grid_point(p.x(), p.y() + 1));
	paint_blank_area(Grid_point(p.x(), p.y() - 1));
}

