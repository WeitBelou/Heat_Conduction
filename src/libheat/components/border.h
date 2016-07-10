#ifndef BORDER_H
#define BORDER_H

#include <QTextStream>
#include <QLineF>

class Border : public QLineF
{
public:
	Border();
	Border(QLineF line, float u);
	Border(QPointF p1, QPointF p2, float u);

	float u() const;
	void setU(float u);

	friend QTextStream &operator<<(QTextStream &os, const Border &b);
	friend QTextStream &operator>>(QTextStream &is, Border &b);

private:
	double m_u;
};

#endif // BORDER_H
