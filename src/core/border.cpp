#include "border.h"


Point::Point()
{
	m_x = m_y = 0;
}

Point::Point(double x, double y)
{
	m_x = x;
	m_y = y;
}

Point::~Point()
{

}

double Point::x() const
{
	return m_x;
}

double Point::y() const
{
	return m_y;
}

bool Point::operator ==(const Point &p) const
{
	return x() == p.x() && y() == p.y();
}

bool Point::operator !=(const Point &p) const
{
	return !(*this == p);
}

QTextStream &operator<<(QTextStream &os, const Point &p)
{
	os << "(" << p.x() << ", " << p.y() << ")";
	return os;
}

QTextStream &operator>>(QTextStream &is, Point &p)
{
	QChar ch;

	is >> ch;
	is >> p.m_x;
	is >> ch;
	is.skipWhiteSpace();
	is >> p.m_y;
	is >> ch; // (d, d)

	return is;
}

/******************************************************************************/

Border::Border()
{
	m_first = Point();
	m_second = Point();

	m_u = 0;
}

Border::Border(Point first, Point second, double u)
{
	m_first = first;
	m_second = second;
	m_u = u;
}

Border::~Border()
{

}

const Point Border::first() const
{
	return m_first;
}

const Point Border::second() const
{
	return m_second;
}

double Border::u() const
{
	return m_u;
}

bool Border::checkIntersect(const Border &b) const
{
	// x = x_1 + (x_2 - x_1) * t, 0 < t < 1
	// y = y_1 + (y_2 - y_1) * t, 0 < t < 1

	double x_11 = first().x();
	double x_12 = second().x();
	double y_11 = first().y();
	double y_12 = second().y();

	double x_21 = b.first().x();
	double x_22 = b.second().x();
	double y_21 = b.first().y();
	double y_22 = b.second().y();

	double d_x = x_21 - x_11;
	double d_y = y_21 - y_11;

	double a_1 = x_12 - x_11;
	double b_1 = y_12 - y_11;
	double a_2 = x_22 - x_21;
	double b_2 = y_22 - y_21;

	double t_1 = d_x / a_1 + (a_2 / a_1) * (d_y - d_x * b_1 / a_1) / (a_2 * b_1 / a_1 - b_2);
	double t_2 = (d_y - d_x * b_1 / a_1) / (a_2 * b_1 / a_1 - b_2);

	if (0 < t_1 && t_1 < 1 && 0 < t_2 && t_2 < 1) {
		return true;
	}
	else {
		return false;
	}
}


QTextStream &operator<<(QTextStream &os, const Border &b)
{
	os << b.first() << " " << b.second() << " " << b.u();
	return os;
}

QTextStream &operator>>(QTextStream &is, Border &b)
{
	is >> b.m_first;
	is.skipWhiteSpace();
	is >> b.m_second;
	is.skipWhiteSpace();
	is >> b.m_u;
	return is;
}
