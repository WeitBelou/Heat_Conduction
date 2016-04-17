/*
 */

#include "parser.h"

QVector<Border> parsePlainText(QString src)
{
	QVector<Border> data;
	size_t i = 0;

	if (src.isEmpty()) {
		throw ParseError("Is empty");
	}

	QTextStream str(&src);

	for (QString s: str.readAll().split("\n")) {
		try {
			if (!s.isEmpty()){
				i++;
				data.push_back(parseLine(s));
			}
		}
		catch (ParseError & p) {
			QString what;
			int where = i;
			what += p.what();
			throw ParseError(what, where);
		}
	}

	dataChecker(data);

	return data;
}


Border parseLine(QString st)
{
	//const char * floatToken = "[+-]?\\d*\\.\\d+";
	QRegExp good("(\\([+-]?\\d*\\.\\d+\\,\\s[+-]?\\d*\\.\\d+\\)\\s){2}[+-]?\\d*\\.\\d+");

	if (!good.exactMatch(st)) {
		throw ParseError("Bad format");
	}

	QTextStream s(&st, QIODevice::ReadOnly);
	Border b;
	s >> b;
	return b;
}

/******************************************************************************/
ParseError::ParseError():
	m_what("Unknow ParseError"), m_where(-1)
{

}

ParseError::ParseError(const QString &what, const int where):
	m_what(what), m_where(where)
{

}

const QString ParseError::what() const noexcept
{
	return m_what;
}

int ParseError::where() const noexcept
{
	return m_where;
}

/******************************************************************************/

void dataChecker(const QVector<Border> &data)
{
	for (int i = 1; i < data.size(); i++) {
		if (data[i - 1].second() != data[i].first()) {
			QString what("Region must be closed");
			int where = i;

			throw ParseError(what, where);
		}

		if (data[i].first() == data[i].second()) {
			QString what("Border can\'t be one point");
			int where = i;

			throw ParseError(what, where);
		}
	}

	if (data.front().first() != data.back().second()) {
		throw ParseError("First point must be equal to last", 1);
	}

	for (int i = 0; i < data.size(); i++) {
		for (int j = i; j < data.size(); j++) {
			if (data[i].checkIntersect(data[j])) {
				QString what;
				int where = i + 1;
				what += "Borders intersect";
				throw ParseError(what, where);
			}
		}
	}
}
