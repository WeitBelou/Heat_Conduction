#ifndef BORDER_H
#define BORDER_H

#include <QTextStream>
#include "point.h"

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
