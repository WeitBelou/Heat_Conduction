#include "border_interpreter.h"

//Конструктор по умолчанию
BorderInterpreter::BorderInterpreter(QObject *parent)
	: QObject(parent),
	  m_maxPointsPerDimension(0),
	  m_minPointsPerDimension(0),
	  m_minPointsBetweenBorders(0),
	  logpath("./log")
{
	this->m_workingArea = TFGeometry();
}

//Основной конструктор
BorderInterpreter::BorderInterpreter(const QVector<Border>& Borders,
					const int maxPointsPerDimension,
					const int minPointsPerDimension,
					const int minPointsBetweenBorders, QObject *parent)
	: QObject(parent),
	m_maxPointsPerDimension(maxPointsPerDimension),
	m_minPointsPerDimension(minPointsPerDimension),
	m_minPointsBetweenBorders(minPointsBetweenBorders),
	logpath("./log")
{
	//Открытие файла лога
	QFile log(logpath);
	if (!log.open(QIODevice::WriteOnly))
		qDebug() << "Failed to create log file" << endl;
	else
		logstream.setDevice(&log);

	qDebug() << "Start border interpretation" << endl;
	logstream << "Start border interpretation" << endl;


	//рассчёт параметров области построения
	qDebug() << "Area analysis" << endl;
	logstream << "Area analysis" << endl;
	findAreaParameters(Borders);
	qDebug() << "Area analysis done" << endl;
	logstream << "Area analysis" << endl;

	//создание сетки
	qDebug() << "Grid construction" << endl;
	logstream << "Grid construction" << endl;
	makeGrid();
	qDebug() << "Grid is builded" << endl;
	logstream << "Grid is builded" << endl;

	//нанесение границ
	qDebug() << "Borders drawing" << endl;
	logstream << "Borders drawing" << endl;
	drawBorders(Borders, 200);
	qDebug() << "Borders are drawn" << endl;
	logstream << "Borders are drawn" << endl;

	//заполнение области вне тела
	QVector<GridPoint> set1, set2;
	qDebug() << "Blank area painting" << endl;
	logstream << "Blank area painting" << endl;
	set1 << GridPoint(0, 0);
	paintBlankArea(set1, set2);
	qDebug() << "Blank area is painted" << endl;
	logstream << "Blank area is painted" << endl;

	qDebug() << "Border interpretation is done" << endl;
	logstream << "Border interpretation is done, closing the logfile" << endl;
	log.close();
}

//Деструктор
BorderInterpreter::~BorderInterpreter()
{
	qDebug() << "Border interpretation destructor" << endl;
}

TFGeometry BorderInterpreter::workingArea() const
{
	return m_workingArea;
}

//Вычисление основных параметров будущей сетки: абсолютных размеров и мелкости
void BorderInterpreter::findAreaParameters(const QVector<Border>& Borders)
{
	qDebug() << "Data Analysis start" << endl;
	logstream << "Data Analysis start" << endl;

	xMax = xMin = Borders[0].first().x();
	yMax = yMin = Borders[0].first().y();
	xMinDist = yMinDist = std::numeric_limits<double>::max();


	for(int i = 0, max = Borders.size(); i < max; i++) {
		if(xMax < Borders[i].first().x())
			xMax = Borders[i].first().x();
		if(xMax < Borders[i].second().x())
			xMax = Borders[i].first().x();

		if(yMax < Borders[i].first().y())
			yMax = Borders[i].first().y();
		if(yMax < Borders[i].second().y())
			yMax = Borders[i].first().y();

		if(xMin > Borders[i].first().x())
			xMin = Borders[i].first().x();
		if(xMin > Borders[i].second().x())
			xMin = Borders[i].first().x();

		if(yMin > Borders[i].first().y())
			yMin = Borders[i].first().y();
		if(yMin > Borders[i].second().y())
			yMin = Borders[i].first().y();

	}

	length = xMax - xMin;
	height = yMax - yMin;

	qDebug() << "Length - " << length << ", height - " << height << endl;
	logstream << "Length - " << length << ", height - " << height << endl;

	//здесь должен быть рассчёт минимальных расстояний
	//временная замена(или не очень временная)
	m_workingArea.setXStep(length / m_maxPointsPerDimension);
	m_workingArea.setYStep(height / m_maxPointsPerDimension);

	qDebug() << "x step - " << m_workingArea.xStep()
			 << ", y step - " << m_workingArea.yStep() << endl;
	logstream << "x step - " << m_workingArea.xStep()
			  << ", y step - " << m_workingArea.yStep() << endl;

	//небольшое отступление от границ
	xMax += 10*m_workingArea.xStep();
	xMin -= 10*m_workingArea.xStep();
	length += 20*m_workingArea.xStep();
	yMax += 10*m_workingArea.yStep();
	yMin -= 10*m_workingArea.yStep();
	height += 20*m_workingArea.yStep();

	//нахождение размеров сетки
	iMax = length / m_workingArea.xStep();
	jMax = height / m_workingArea.yStep();


	qDebug() << "Final length - " << length << ", final height - " << height << endl;
	logstream << "Final length - " << length << ", final height - " << height << endl;
	qDebug() << "x min dist - " << xMinDist << ", y min dist - " << yMinDist << endl;
	logstream << "x min dist - " << xMinDist << ", y min dist - " << yMinDist << endl;
	qDebug() << "iMax - " << iMax << ", jMax - "
			 << jMax << endl;
	logstream << "iMax - " << iMax << ", jMax - "
			  << jMax << endl;

}

//Построение сетки
void BorderInterpreter::makeGrid()
{
	qDebug() << "Grid construction start" << endl;
	logstream << "Grid construction start" << endl;

	m_workingArea.setZeroLayer(TemperatureField(iMax, jMax));
	m_workingArea.setIdNet(BoolGrid(iMax, jMax));

	//Заполнение сеткок
	qDebug() << "Grid construction done, filling the grid" << endl;
	logstream << "Grid construction done, filling the grid" << endl;
	for(int i = 0; i < iMax; i++) {
		for(int j = 0; j < jMax; j++) {
			m_workingArea.idNet()(i, j) = true;
			m_workingArea.zeroLayer()(i, j) = 0;
		}
	}
}


//Нанесение границ
void BorderInterpreter::drawBorders(const QVector<Border>& Borders, int accuracy)
{
	qDebug() << "Border drawing start" << endl;
	logstream << "Border drawing start" << endl;

	//Выбор точки следующей точки границы осуществляется с помощью вектора
	//от текущей точки к конечной; из-за особенности алгоритма требутеся разбиение
	//линий границ на множество меньших линий границ
	for(Border b: Borders) {

		GridPoint p1 = pToGp(b.first());
		GridPoint pEnd = pToGp(b.second());

		//разбиение отрезка границы на отрезки подграниц
		int numberOfSublines = accuracy * sqrt(   1.0 * (  (pEnd.x()-p1.x()) * (pEnd.x()-p1.x()) +
										(pEnd.y()-p1.y()) * (pEnd.y()-p1.y())  ) /
										(iMax*iMax + jMax*jMax)   );
		if(numberOfSublines < 1 )
			numberOfSublines = 1;


		GridPoint * p2 = new GridPoint[numberOfSublines];
		for(int i = 0; i < numberOfSublines - 1; i++) {
			p2[i] = p1 + (pEnd - p1)*( 1.0 * (i+1) / numberOfSublines);
		}
		p2[numberOfSublines-1] = pEnd;

		for(int i = 0; i < numberOfSublines; i++) {
			while(p1 != p2[i]) {
				putPoint(p1, b.u());
				p1 = movePoint(p1, p2[i]);
			}
		}

		delete [] p2;
		qDebug() << "Border is set" << endl;
		logstream << "Border is set" << endl;
	}
}

//Перевод точки из абсолютной системы в сетку
GridPoint BorderInterpreter::pToGp(const Point& p)
{
	return GridPoint(	(p.x() - xMin) / m_workingArea.xStep(),
						(p.y() - yMin) / m_workingArea.yStep());
}

//Выбор следующей точки границы
GridPoint BorderInterpreter::movePoint(const GridPoint& p1, const GridPoint& p2)
{
	if(p1 == p2)
		return p1;

	if( std::fabs(p2.x() - p1.x()) > std::fabs(p2.y() - p1.y()) ) {
		if( (p2.x() - p1.x()) > 0)
			return GridPoint( p1.x() + 1, p1.y() );
		else
			return GridPoint( p1.x() - 1, p1.y() );
	}
	else
	{
		if( (p2.y() - p1.y()) > 0)
			return GridPoint( p1.x(), p1.y() + 1 );
		else
			return GridPoint( p1.x(), p1.y() - 1 );
	}
}

//Нанесение точки границы на сетку
void BorderInterpreter::putPoint(const GridPoint& p, const double& u)
{
	m_workingArea.zeroLayer()(p.x(), p.y()) = u;
	m_workingArea.idNet()(p.x(), p.y()) = false;
}

//Заполнение области вне тела
void BorderInterpreter::paintBlankArea(QVector<GridPoint>& set1, QVector<GridPoint>& set2)
{
	if(set1.isEmpty())
		return;

	for(auto it = set1.cbegin(); it != set1.cend(); ++it) {
		if( it->x() < 0 || it->x() > iMax-1 || it->y() < 0 || it->y() > jMax-1)
			continue;
		if(m_workingArea.idNet()(it->x(), it->y()) == false)
			continue;
		m_workingArea.idNet()(it->x(), it->y()) = false;
		set2 << GridPoint(it->x() + 1, it->y()) << GridPoint(it->x() - 1, it->y()) <<
				GridPoint(it->x(), it->y() + 1) << GridPoint(it->x(), it->y() - 1);
	}

	set1.clear();
	paintBlankArea(set2, set1);
}

