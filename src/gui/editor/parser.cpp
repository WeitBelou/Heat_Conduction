/*
 */

#include "parser.h"
using namespace Parser;

QVector<QVector<Border>> MultiParse( QString src ){

	QVector<QVector<Border>> data;
	//QString tmp;
	int i;

	if ( src.trimmed().isEmpty() ) {
		throw ParseError("Empty input!");
	}

	src.remove(QChar('{'), Qt::CaseInsensitive);

	if ( src.lastIndexOf("}") != -1 )
	{
		i = src.lastIndexOf( "}" );
		src.remove( i, 1 );
	}

	QTextStream str( &src );
	i = 0;

	for (QString s: str.readAll().split("}")) {
		try {
			if (!s.trimmed().isEmpty()){
				i++;
				data.push_back(parsePlainText(s));
			}
		}
		catch (ParseError & p) {
			QString what = p.what();
			QString where = QString("On line: %1").arg(i + 1);
			throw ParseError(what, where);
		}
	}

	dataChecker(data);

	return data;
}

QVector<Border> parsePlainText(QString src)
{
	QVector<Border> data;
	size_t i = 0;

	if (src.trimmed().isEmpty()) {
		throw ParseError("Is empty");
	}

	QTextStream str(&src);

	for (QString s: str.readAll().split("\n")) {
		try {
			if (!s.trimmed().isEmpty()){
				i++;
				data.push_back(parseBorder(s));
			}
		}
		catch (ParseError & p) {
			QString what = p.what();
			QString where = QString("On line: %1").arg(i + 1);
			throw ParseError(what, where);
		}
	}

	onePolyCheck(data);

	return data;
}


Border parseBorder(QString st)
{
	if (!QRegExp(m_borderToken).exactMatch(st)) {
		throw ParseError("Bad format");
	}

	QTextStream s(&st, QIODevice::ReadOnly);
	Border b;
	s >> b;
	return b;
}

/******************************************************************************/
ParseError::ParseError():
	m_what("Unknow ParseError"), m_where(QString(""))
{

}

ParseError::ParseError(const QString &what, const QString &where):
	m_what(what), m_where(where)
{

}

const QString ParseError::what() const noexcept
{
	return m_what;
}

const QString ParseError::where() const noexcept
{
	return m_where;
}

/******************************************************************************/

void dataChecker(const QVector<QVector<Border> > & data)
{
	int N = data.size();

	for (int i = 0; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {
			twoPolyCheck(data[i], data[j]);
		}
	}
}

void onePolyCheck(const QVector<Border> & data)
{
	int N = data.size();
	for (int i = 1; i < N; i++) {
		if (data[i - 1].p2() != data[i].p1()) {
			QString what("Region must be closed");
			QString where = QString("On lines: %1 and %2").arg(i, i + 1);

			throw ParseError(what, where);
		}

		if (data[i - 1].p1() == data[i - 1].p2()) {
			QString what("Border can\'t be one point");
			QString where = QString("On line: %1").arg(i + 1);

			throw ParseError(what, where);
		}
	}

	if (data.front().p1() != data.back().p2()) {
		throw ParseError("First point must be equal to last");
	}

	QPointF tmp;
	for (int i = 0; i < data.size(); i++) {
		for (int j = i; j < data.size(); j++) {
			if (data[i].intersect(data[j], &tmp) == QLineF::BoundedIntersection) {
				if (tmp == data[i].p2() || tmp == data[j].p2()) {
					continue;
				}
				QString what("Borders intersect");
				QString where = QString("On lines: %1 and %2").arg(i + 1, j + 1);
				throw ParseError(what, where);
			}
		}
	}
}

void twoPolyCheck(const QVector<Border> & a, const QVector<Border> & b)
{
	int N = a.size();
	int M = b.size();

	QPointF tmp;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (a[i].intersect(b[j], &tmp) == QLineF::BoundedIntersection) {
				QString what("Polygons intersect");
				QString where = QString("On lines: %1 and %2").arg(i + 1).arg(j + 1);
				throw ParseError(what, where);
			}
		}
	}
}
