#include "border.h"

Border::Border() :
	QLineF(), m_u(0)
{

}

Border::Border(QLineF line, double u) :
	QLineF(line), m_u(u)
{

}

Border::Border(QPointF p1, QPointF p2, double u) :
	QLineF(p1, p2), m_u(u)
{

}

double Border::u() const
{
	return m_u;
}

void Border::setU(double u)
{
	m_u = u;
}

QTextStream &operator<<(QTextStream &os, const Border &b)
{
	os << "(" << b.x1() << ", " << b.y1() << ")" << " " <<
		  "(" << b.x2() << ", " << b.y2() << ")" << " " <<
		  b.u();

	return os;
}

QTextStream &operator>>(QTextStream &is, Border &b)
{
	double x1, y1, x2, y2, u;
	QChar ch;

	is >> ch;
	is >> x1;
	is >> ch;
	is.skipWhiteSpace();
	is >> y1;
	is >> ch;

	is.skipWhiteSpace();

	is >> ch;
	is >> x2;
	is >> ch;
	is.skipWhiteSpace();
	is >> y2;
	is >> ch;

	is.skipWhiteSpace();
	is >> u;

	b.setLine(x1, y1, x2, y2);
	b.setU(u);

	return is;
}
