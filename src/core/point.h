#ifndef POINT_H
#define POINT_H
#include <QTextStream>

template <typename T>
class TemplatePoint
{
public:
	TemplatePoint();
	TemplatePoint(T x, T y);
	~TemplatePoint();

	T x() const;
	T y() const;

	bool operator ==(const TemplatePoint<T>& p) const;
	bool operator !=(const TemplatePoint<T>& p) const;
	void operator = (const TemplatePoint<T>& p);
	TemplatePoint<T> operator + (const TemplatePoint<T>& p) const;
	TemplatePoint<T> operator - (const TemplatePoint<T>& p) const;
	TemplatePoint<T> operator * (const double& m) const;

	template <typename T1>
	friend QTextStream &operator<<(QTextStream &os, const TemplatePoint<T1> &p);

	template <typename T1>
	friend QTextStream &operator>>(QTextStream &is, TemplatePoint<T1> &p);
private:
	T m_x, m_y;
};

typedef TemplatePoint<double> Point;
typedef TemplatePoint<int> GridPoint;

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
void TemplatePoint<T>::operator = (const TemplatePoint<T>& p)
{
	if(*this == p) {
		return;
	}
	m_x = p.m_x;
	m_y = p.m_y;
}

template <typename T>
TemplatePoint<T> TemplatePoint<T>::operator + (const TemplatePoint<T>& p) const{
	return TemplatePoint<T>(m_x + p.x(), m_y + p.y());
}

template <typename T>
TemplatePoint<T> TemplatePoint<T>::operator - (const TemplatePoint<T>& p) const{
	return TemplatePoint<T>(m_x - p.x(), m_y - p.y());
}

template <typename T>
TemplatePoint<T> TemplatePoint<T>::operator * (const double& m) const{
	return TemplatePoint<T>(m_x * m, m_y * m);
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

#endif // POINT_H

