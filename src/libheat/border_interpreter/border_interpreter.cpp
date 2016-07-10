#include "border_interpreter.h"

//Конструктор по умолчанию
BorderInterpreter::BorderInterpreter(QObject *parent)
	: QObject(parent),
	  m_maxPointsPerDimension(0),
	  m_minPointsPerDimension(0),
	  m_minPointsBetweenBorders(0),
	  m_workingArea()
{

}

//Основной конструктор
BorderInterpreter::BorderInterpreter(const QVector<Border>& borders,
					const int maxPointsPerDimension,
					const int minPointsPerDimension,
					const int minPointsBetweenBorders, QObject *parent)
	: QObject(parent),
	m_maxPointsPerDimension(maxPointsPerDimension),
	m_minPointsPerDimension(minPointsPerDimension),
	m_minPointsBetweenBorders(minPointsBetweenBorders),
	borders(borders)
{

}

void BorderInterpreter::solve()
{

	emit logSent(QString("Start border interpretation"));


	//рассчёт параметров области построения
	findAreaParameters();

	//создание сетки
	makeGrid();

	//нанесение границ
	drawBorders(std::min(iMax, jMax) / 2);

	//заполнение области вне тела
	QVector<QPoint> vector1;
	QVector<QPoint> vector2;
	emit logSent(QString("Painting blank area"));
	vector1 << QPoint(0, 0);
	paintBlankArea(vector1, vector2);
	emit logSent(QString("Blank area is painted"));

	emit logSent(QString("Border interpretation is done"));
}

//Деструктор
BorderInterpreter::~BorderInterpreter()
{
	emit logSent(QString("Border interpretation destructor"));
}

TFGeometry BorderInterpreter::workingArea() const
{
	return m_workingArea;
}

//Вычисление основных параметров будущей сетки: абсолютных размеров и мелкости
void BorderInterpreter::findAreaParameters()
{
	emit logSent(QString("Data Analysis start"));

	findLengthHeight();
	emit logSent(QString("Length - %1, height - %2").arg(length).arg(height));

	findMinimalDistances();
	emit logSent(QString("x minimal distance - %1, y minimal distance - %2").arg(xMinDist).arg(yMinDist));

	findStep();
	emit logSent(QString("x step - %1, y step - %2").arg(m_workingArea.xStep()).arg(m_workingArea.yStep()));


	//небольшое отступление от границ
	xMax += 10*m_workingArea.xStep();
	xMin -= 10*m_workingArea.xStep();
	length += 20*m_workingArea.xStep();
	yMax += 10*m_workingArea.yStep();
	yMin -= 10*m_workingArea.yStep();
	height += 20*m_workingArea.yStep();

	//нахождение размеров сетки
	iMax = static_cast<int>(length / m_workingArea.xStep());
	jMax = static_cast<int>(height / m_workingArea.yStep());


	emit logSent(QString("Final length - %1, final height - %2").arg(length).arg(height));
	emit logSent(QString("x min dist - %1, y min dist - %2").arg(xMinDist).arg(yMinDist));
	emit logSent(QString("x step - %1, y step - %2").arg(m_workingArea.xStep()).arg(m_workingArea.yStep()));
	emit logSent(QString("iMax - %1, jMax - %2").arg(iMax).arg(jMax));
	emit logSent(QString("Area analysis done"));

}

void BorderInterpreter::findLengthHeight()
{
	xMax = xMin = static_cast<float>(borders[0].x1());
	yMax = yMin = static_cast<float>(borders[0].y1());

	for(int i = 0, max = borders.size(); i < max; i++) {
		if(xMax < borders[i].x1())
			xMax = static_cast<float>(borders[i].x1());

		if(yMax < borders[i].y1())
			yMax = static_cast<float>(borders[i].y1());

		if(xMin > borders[i].x1())
			xMin = static_cast<float>(borders[i].x1());

		if(yMin > borders[i].y1())
			yMin = static_cast<float>(borders[i].y1());
	}

	length = xMax - xMin;
	height = yMax - yMin;

}

void BorderInterpreter::findMinimalDistances()
{
	xMinDist = yMinDist = std::numeric_limits<double>::max();

	for(int i = 0, max = borders.size(); i < max; i++) {
		for(int j = i+1, max = borders.size(); j < max; j++) {
			if(fabs(borders[j].x1() - borders[i].x1()) < xMinDist &&
					fabs(borders[j].x1() - borders[i].x1()) > length / m_maxPointsPerDimension)
				xMinDist = fabs(borders[j].x1() - borders[i].x1());
			if(fabs(borders[j].y1() - borders[i].y1()) < yMinDist &&
					fabs(borders[j].y1() - borders[i].y1()) > height / m_maxPointsPerDimension)
				yMinDist = fabs(borders[j].y1() - borders[i].y1());
		}
	}

	xMinDist /= m_minPointsBetweenBorders;
	yMinDist /= m_minPointsBetweenBorders;

}

void BorderInterpreter::findStep()
{
	if((length / xMinDist) < m_minPointsPerDimension)
		xMinDist = length / m_minPointsPerDimension;
	else if((length / xMinDist) > m_maxPointsPerDimension)
		xMinDist = length / m_maxPointsPerDimension;

	emit logSent(QString("1: x minimal distance - %1, y minimal distance - %2").arg(xMinDist).arg(yMinDist));

	if((height / yMinDist) < m_minPointsPerDimension)
		yMinDist = height / m_minPointsPerDimension;
	else if((height / yMinDist) > m_maxPointsPerDimension)
		yMinDist = height / m_maxPointsPerDimension;

	emit logSent(QString("2: x minimal distance - %1, y minimal distance - %2").arg(xMinDist).arg(yMinDist));

	xMinDist = std::min(xMinDist, yMinDist);
	yMinDist = std::min(xMinDist, yMinDist);

	emit logSent(QString("3: x minimal distance - %1, y minimal distance - %2").arg(xMinDist).arg(yMinDist));

	if((length / xMinDist) > m_maxPointsPerDimension) {
		xMinDist = length / m_maxPointsPerDimension;
		yMinDist = length / m_maxPointsPerDimension;
	}

	if((height / yMinDist) > m_maxPointsPerDimension) {
		xMinDist = height / m_maxPointsPerDimension;
		yMinDist = height / m_maxPointsPerDimension;
	}

	emit logSent(QString("4: x minimal distance - %1, y minimal distance - %2").arg(xMinDist).arg(yMinDist));

	m_workingArea.setXStep(xMinDist);
	m_workingArea.setYStep(yMinDist);
}

//Построение сетки
void BorderInterpreter::makeGrid()
{
	emit logSent(QString("Grid construction start"));

	m_workingArea.setZeroLayer(TemperatureField(iMax, jMax));
	m_workingArea.setIdNet(BoolGrid(iMax, jMax));

	//Заполнение сеткок
	emit logSent(QString("Grid construction done, filling the grid"));
	for(int i = 0; i < iMax; i++) {
		for(int j = 0; j < jMax; j++) {
			m_workingArea.idNet()(i, j) = true;
			m_workingArea.zeroLayer()(i, j) = 0;
		}
	}

	emit logSent(QString("Grid is builded"));
}


//Нанесение границ
void BorderInterpreter::drawBorders(int accuracy)
{
	emit logSent(QString("Border drawing start"));

	//Выбор точки следующей точки границы осуществляется с помощью вектора
	//от текущей точки к конечной; из-за особенности алгоритма требутеся разбиение
	//линий границ на множество меньших линий границ
	for(Border b: borders) {

		QPoint p1 = pToGp(b.p1());
		QPoint pEnd = pToGp(b.p2());

		//разбиение отрезка границы на отрезки подграниц
		int numberOfSublines = accuracy * sqrt(
					1.0 * (  (pEnd.x()-p1.x()) * (pEnd.x()-p1.x()) +
					(pEnd.y()-p1.y()) * (pEnd.y()-p1.y())  ) /
					(iMax*iMax + jMax*jMax)   );
		if(numberOfSublines < 1 )
			numberOfSublines = 1;


		QPoint* p2 = new QPoint[numberOfSublines];
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
		emit logSent(QString("Border is set"));
	}

	emit logSent(QString("Borders are drawn"));
}

//Перевод точки из абсолютной системы в сетку
QPoint BorderInterpreter::pToGp(const QPointF& p)
{
	return QPoint(	(p.x() - xMin) / m_workingArea.xStep(),
						(p.y() - yMin) / m_workingArea.yStep());
}

//Выбор следующей точки границы
QPoint BorderInterpreter::movePoint(const QPoint& p1, const QPoint& p2)
{
	if(p1 == p2)
		return p1;

	if( std::fabs(p2.x() - p1.x()) > std::fabs(p2.y() - p1.y()) ) {
		if( (p2.x() - p1.x()) > 0)
			return QPoint( p1.x() + 1, p1.y() );
		else
			return QPoint( p1.x() - 1, p1.y() );
	}
	else
	{
		if( (p2.y() - p1.y()) > 0)
			return QPoint( p1.x(), p1.y() + 1 );
		else
			return QPoint( p1.x(), p1.y() - 1 );
	}
}

//Нанесение точки границы на сетку
void BorderInterpreter::putPoint (const QPoint &p, const float &u)
{
	m_workingArea.zeroLayer()(p.x(), p.y()) = u;
	m_workingArea.idNet()(p.x(), p.y()) = false;
}

//Заполнение области вне тела
void BorderInterpreter::paintBlankArea(QVector<QPoint>& vector1, QVector<QPoint>& vector2)
{
	if(vector1.isEmpty())
		return;

	for(auto it = vector1.cbegin(); it != vector1.cend(); ++it) {
		if( it->x() < 0 || it->x() > iMax-1 || it->y() < 0 || it->y() > jMax-1)
			continue;
		if(m_workingArea.idNet()(it->x(), it->y()) == false)
			continue;
		m_workingArea.idNet()(it->x(), it->y()) = false;
		vector2 << QPoint(it->x() + 1, it->y()) << QPoint(it->x() - 1, it->y()) <<
				QPoint(it->x(), it->y() + 1) << QPoint(it->x(), it->y() - 1);
	}

	vector1.clear();
	paintBlankArea(vector2, vector1);
}

