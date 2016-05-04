#ifndef BORDER_H
#define BORDER_H

#include <QTextStream>
#include <QPointF>
#include <QLineF>

class Border : public QLineF
{
public:
	Border();
	Border(QLineF line, double u);
	Border(QPointF p1, QPointF p2, double u);

	double u() const;
	void setU(double u);

	friend QTextStream &operator<<(QTextStream &os, const Border &b);
	friend QTextStream &operator>>(QTextStream &is, Border &b);

private:
	double m_u;
};

#endif // BORDER_H
