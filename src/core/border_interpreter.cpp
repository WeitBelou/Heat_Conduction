#include "border_interpreter.h"

//Конструктор по умолчанию
Border_interpreter::Border_interpreter() :
	log("./log")
{
	this->argument_for_calc = ArgumentForCalc();
}

//Основной конструктор
Border_interpreter::Border_interpreter(const QVector<Border>& Borders,
					const int max_number_of_points_per_dimension,
					const int min_number_of_points_per_dimension,
					const int min_number_of_points_between_close_borders)
	: log("./log")
{
	//Открытие файла лога
	if (!log.open(QIODevice::WriteOnly))
		qDebug() << "Failed to create log file" << endl;
	else
		logstream.setDevice(&log);

	qDebug() << "Start border interpretation" << endl;
	logstream << "Start border interpretation" << endl;

	//тестовые значения
	argument_for_calc.p = argument_for_calc.c = argument_for_calc.lmbd = 2;
	argument_for_calc.tMax = 100;
	argument_for_calc.tStep = 0.01;


	//рассчёт параметров области построения
	qDebug() << "Area analysis" << endl;
	logstream << "Area analysis" << endl;
	find_area_parameters(Borders, max_number_of_points_per_dimension,
						 min_number_of_points_per_dimension,
						 min_number_of_points_between_close_borders);
	qDebug() << "Area analysis done" << endl;
	logstream << "Area analysis" << endl;

	//создание сетки
	qDebug() << "Grid construction" << endl;
	logstream << "Grid construction" << endl;
	make_grid();
	qDebug() << "Grid is builded" << endl;
	logstream << "Grid is builded" << endl;

	//нанесение границ
	qDebug() << "Borders drawing" << endl;
	logstream << "Borders drawing" << endl;
	draw_borders(Borders);
	qDebug() << "Borders are drawn" << endl;
	logstream << "Borders are drawn" << endl;

	//заполнение области вне тела
	qDebug() << "Blank area painting" << endl;
	logstream << "Blank area painting" << endl;
	paint_blank_area(0, 0);
	qDebug() << "Blank area is painted" << endl;
	logstream << "Blank area is painted" << endl;

	qDebug() << "Border interpretation is done" << endl;
	logstream << "Border interpretation is done" << endl;
}

//Деструктор
Border_interpreter::~Border_interpreter()
{
	qDebug() << "Border interpretation destructor" << endl;
	logstream << "Border interpretation destructor" << endl;
	log.close();
}

//Гетер важной структуры
ArgumentForCalc Border_interpreter::get_argument_for_calc()
{
	return argument_for_calc;
}

//Вычисление основных параметров будущей сетки: абсолютных размеров и мелкости
void Border_interpreter::find_area_parameters(const QVector<Border>& Borders,
					const int& max_number_of_points_per_dimension,
					const int& min_number_of_points_per_dimension,
					const int& min_number_of_points_between_close_borders)
{
	qDebug() << "Data Analysis start" << endl;
	logstream << "Data Analysis start" << endl;

	x_max = x_min = Borders[0].first().x();
	y_max = y_min = Borders[0].first().y();
	x_min_dist = y_min_dist = std::numeric_limits<double>::max();


	for(int i = 0, max = Borders.size(); i < max; i++) {
		if(x_max < Borders[i].first().x())
			x_max = Borders[i].first().x();
		if(x_max < Borders[i].second().x())
			x_max = Borders[i].first().x();

		if(y_max < Borders[i].first().y())
			y_max = Borders[i].first().y();
		if(y_max < Borders[i].second().y())
			y_max = Borders[i].first().y();

		if(x_min > Borders[i].first().x())
			x_min = Borders[i].first().x();
		if(x_min > Borders[i].second().x())
			x_min = Borders[i].first().x();

		if(y_min > Borders[i].first().y())
			y_min = Borders[i].first().y();
		if(y_min > Borders[i].second().y())
			y_min = Borders[i].first().y();

	}

	length = x_max - x_min;
	height = y_max - y_min;

	qDebug() << "Length - " << length << ", height - " << height << endl;
	logstream << "Length - " << length << ", height - " << height << endl;


	//использовалось для оптимального определения мелкости сетки
	//нужно переделать вместе с функцией check_min_dist

	/*
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

	x_max += 2*argument_for_calc.xStep;
	x_min -= 2*argument_for_calc.xStep;
	length += 4*argument_for_calc.xStep;
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
	*/

	//временная замена предыдущему блоку
	argument_for_calc.xStep = length / max_number_of_points_per_dimension;
	argument_for_calc.yStep = height / max_number_of_points_per_dimension;

	qDebug() << "x step - " << argument_for_calc.xStep
			 << ", y step - " << argument_for_calc.yStep << endl;
	logstream << "x step - " << argument_for_calc.xStep
			  << ", y step - " << argument_for_calc.yStep << endl;

	//небольшое отступление от границ
	x_max += 10*argument_for_calc.xStep;
	x_min -= 10*argument_for_calc.xStep;
	length += 20*argument_for_calc.xStep;
	y_max += 10*argument_for_calc.yStep;
	y_min -= 10*argument_for_calc.yStep;
	height += 20*argument_for_calc.yStep;

	//нахождение размеров сетки
	argument_for_calc.iMax = length / argument_for_calc.xStep;
	argument_for_calc.jMax = height / argument_for_calc.yStep;


	qDebug() << "Final length - " << length << ", final height - " << height << endl;
	logstream << "Final length - " << length << ", final height - " << height << endl;
	qDebug() << "x min dist - " << x_min_dist << ", y min dist - " << y_min_dist << endl;
	logstream << "x min dist - " << x_min_dist << ", y min dist - " << y_min_dist << endl;
	qDebug() << "iMax - " << argument_for_calc.iMax << ", jMax - "
			 << argument_for_calc.jMax << endl;
	logstream << "iMax - " << argument_for_calc.iMax << ", jMax - "
			  << argument_for_calc.jMax << endl;

}

//нахождение минимальных расстояний, требуется доработка
 /*
void Border_interpreter::check_min_dist(const QVector<Border>& Borders,
							const int& i, const int& j,
							const int& max_number_of_points_per_dimension,
							const int& min_number_of_points_per_dimension,
							const int& min_number_of_points_between_close_borders)
{
	if(	std::fabs(Borders[i].first().x() - Borders[j].first().x()) < x_min_dist	&&
			std::fabs(Borders[i].first().x() - Borders[j].first().x()) > (length / max_number_of_points_per_dimension))

		x_min_dist = std::fabs(Borders[i].first().x() - Borders[j].first().x());

	if(	std::fabs(Borders[i].first().y() - Borders[j].first().y()) < y_min_dist &&
			std::fabs(Borders[i].first().y() - Borders[j].first().y()) > (height / max_number_of_points_per_dimension))

		y_min_dist = std::fabs(Borders[i].first().y() - Borders[j].first().y());
}
*/

//Построение сетки
void Border_interpreter::make_grid()
{
	qDebug() << "Grid construction start" << endl;
	logstream << "Grid construction start" << endl;

	argument_for_calc.zeroLayer = Layer(argument_for_calc.iMax, argument_for_calc.jMax);
	argument_for_calc.idNet = BoolNet(argument_for_calc.iMax, argument_for_calc.jMax);

	//Заполнение сеткок
	for(int i = 0; i < argument_for_calc.iMax; i++) {
		for(int j = 0; j < argument_for_calc.jMax; j++) {
			argument_for_calc.idNet(i, j) = true;
			argument_for_calc.zeroLayer(i, j) = 0;
		}
	}
}


//Нанесение границ
void Border_interpreter::draw_borders(const QVector<Border>& Borders)
{
	qDebug() << "Border drawing start" << endl;
	logstream << "Border drawing start" << endl;

	//Выбор точки следующей точки границы осуществляется с помощью вектора
	//направления от текущей точки к конечной
	Grid_point p1, p2;
	for(Border b: Borders) {
		p1 = p_to_gp(b.first());
		p2 = p_to_gp(b.second());
		put_point(p2, b.u());

		do {
			put_point(p1, b.u());
			p1 = move_point(p1, p2);
		}
		while(p1 != p2);
		qDebug() << "Border is set" << endl;
		logstream << "Border is set" << endl;
	}
}

//Перевод точки из абсолютной системы в сетку
Grid_point Border_interpreter::p_to_gp(const Point& p)
{
	return Grid_point(	(p.x() - x_min) / argument_for_calc.xStep,
						(p.y() - y_min) / argument_for_calc.yStep);
}

//Выбор следующей точки границы
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

//Нанесение точки границы на сетку
void Border_interpreter::put_point(const Grid_point& p, const double& u)
{
	argument_for_calc.zeroLayer(p.x(), p.y()) = u;
	argument_for_calc.idNet(p.x(), p.y()) = false;
}

//Заполнение области вне тела
void Border_interpreter::paint_blank_area(const int& i, const int& j)
{
	if( i < 0 || i > argument_for_calc.iMax-1 || j < 0 || j > argument_for_calc.jMax-1)
		return;
	if( argument_for_calc.idNet(i, j) == false)
		return;

	argument_for_calc.idNet( i, j) = false;
	paint_blank_area(i + 1, j);
	paint_blank_area(i - 1, j);
	paint_blank_area(i, j + 1);
	paint_blank_area(i, j - 1);
}

