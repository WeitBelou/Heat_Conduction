#include "border_interpreter.h"
#include <QPoint>

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
BorderInterpreter::BorderInterpreter(const QVector<Border>& Borders,
					const int maxPointsPerDimension,
					const int minPointsPerDimension,
					const int minPointsBetweenBorders, QObject *parent)
	: QObject(parent),
	m_maxPointsPerDimension(maxPointsPerDimension),
	m_minPointsPerDimension(minPointsPerDimension),
	m_minPointsBetweenBorders(minPointsBetweenBorders)
{

	emit logSent(QString("Start border interpretation"));


	//рассчёт параметров области построения
	findAreaParameters(Borders);

	//создание сетки
	makeGrid();

	//нанесение границ
	drawBorders(Borders, 600);

	//заполнение области вне тела
	QVector<QPoint> vector1;
	QVector<QPoint> vector2;
	emit logSent(QString("Painting blank area"));
	vector1 << QPoint(0, 0);
	paintBlankArea(vector1, vector2);
	emit logSent(QString("Painting blank area"));

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
void BorderInterpreter::findAreaParameters(const QVector<Border>& Borders)
{
	emit logSent(QString("Data Analysis start"));

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

	emit logSent(QString("Length - %1, height - %2").arg(length, height));

	//здесь должен быть рассчёт минимальных расстояний
	//временная замена(или не очень временная)
	m_workingArea.setXStep(length / m_maxPointsPerDimension);
	m_workingArea.setYStep(height / m_maxPointsPerDimension);

	emit logSent(QString("x step - %1, y step - %2").arg(m_workingArea.xStep(), m_workingArea.yStep()));

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


	emit logSent(QString("Final length - %1, final height - %2").arg(length, height));
	emit logSent(QString("x min dist - %1, y min dist - %2").arg(xMinDist, yMinDist));
	emit logSent(QString("iMax - %1, jMax - %2").arg(iMax, jMax));
	emit logSent(QString("Area analysis done"));

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
void BorderInterpreter::drawBorders(const QVector<Border>& Borders, int accuracy)
{
	emit logSent(QString("Border drawing start"));

	//Выбор точки следующей точки границы осуществляется с помощью вектора
	//от текущей точки к конечной; из-за особенности алгоритма требутеся разбиение
	//линий границ на множество меньших линий границ
	for(Border b: Borders) {

		QPoint p1 = pToGp(b.first());
		QPoint pEnd = pToGp(b.second());

		//разбиение отрезка границы на отрезки подграниц
		int numberOfSublines = accuracy * sqrt(
					1.0 * (  (pEnd.x()-p1.x()) * (pEnd.x()-p1.x()) +
					(pEnd.y()-p1.y()) * (pEnd.y()-p1.y())  ) /
					(iMax*iMax + jMax*jMax)   );
		if(numberOfSublines < 1 )
			numberOfSublines = 1;


		QPoint * p2 = new QPoint[numberOfSublines];
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
QPoint BorderInterpreter::pToGp(const Point& p)
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
void BorderInterpreter::putPoint(const QPoint& p, const double& u)
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

