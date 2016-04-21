#ifndef BORDER_H
#define BORDER_H

#include <QTextStream>
#include <QDebug>

template <typename T>
class TemplatePoint
{
public:
	TemplatePoint();
	TemplatePoint(T x, T y);
	~TemplatePoint();

	T x() const;
	T y() const;

	bool operator ==(const TemplatePoint<T> &p) const;
	bool operator !=(const TemplatePoint<T>& p) const;

	template <typename T1>
	friend QTextStream &operator<<(QTextStream &os, const TemplatePoint<T1> &p);

	template <typename T1>
	friend QTextStream &operator>>(QTextStream &is, TemplatePoint<T1> &p);
private:
	T m_x, m_y;
};

typedef TemplatePoint<double> Point;
typedef TemplatePoint<int> Grid_point;

/***********************************************************/
template <typename T>
TemplatePoint<T>::TemplatePoint()
{
	m_x = m_y = 0;
}
template <typename T>
TemplatePoint<T>::TemplatePoint(T x, T y)
{
	m_x = x;
	m_y = y;
}

template <typename T>
TemplatePoint<T>::~TemplatePoint()
{

}

template <typename T>
T TemplatePoint<T>::x() const
{
	return m_x;
}

template <typename T>
T TemplatePoint<T>::y() const
{
	return m_y;
}

template <typename T>
bool TemplatePoint<T>::operator ==(const TemplatePoint<T>& p) const
{
	return x() == p.x() && y() == p.y();
}

template <typename T>
bool TemplatePoint<T>::operator !=(const TemplatePoint<T> &p) const
{
	return !(*this == p);
}

template <typename T>
QTextStream &operator<<(QTextStream &os, const TemplatePoint<T> &p)
{
	os << "(" << p.x() << ", " << p.y() << ")";
	return os;
}

template <typename T>
QTextStream &operator>>(QTextStream &is, TemplatePoint<T> &p)
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
/*************************************************************/



class Border
{
public:
	Border();
	Border(Point first, Point second, double u);
	~Border();

	const Point first() const;
	const Point second() const;
	double u() const;

	bool checkIntersect(const Border &b) const;

	friend QTextStream &operator<<(QTextStream &os, const Border &b);
	friend QTextStream &operator>>(QTextStream &is, Border &b);
private:
	Point m_first, m_second;
	double m_u;
};


#endif // BORDER_H
