/*
 */

#include "parser.h"
using namespace Parser;

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

	dataChecker(data);

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
	m_what("Unknow ParseError"), m_where(QString("Nowhere"))
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

void dataChecker(const QVector<Border> &data)
{
	for (int i = 1; i < data.size(); i++) {
		if (data[i - 1].second() != data[i].first()) {
			QString what("Region must be closed");
			QString where = QString("On lines: %1 and %2").arg(i, i + 1);

			throw ParseError(what, where);
		}

		if (data[i].first() == data[i].second()) {
			QString what("Border can\'t be one point");
			QString where = QString("On line: %1").arg(i + 1);

			throw ParseError(what, where);
		}
	}

	if (data.front().first() != data.back().second()) {
		throw ParseError("First point must be equal to last", "On first and last");
	}

	for (int i = 0; i < data.size(); i++) {
		for (int j = i; j < data.size(); j++) {
			if (data[i].checkIntersect(data[j])) {
				QString what("Borders intersect");
				QString where = QString("On lines: %1 and %2").arg(i + 1, j + 1);
				throw ParseError(what, where);
			}
		}
	}
}
