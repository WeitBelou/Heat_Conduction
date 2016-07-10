/*
 * File:   parser.h
 * Author: ivan
 *
 * Created on 7 апреля 2016 г., 20:33
 */

#ifndef PARSER_H
#define PARSER_H

#include <QVector>
#include <QFile>
#include <QRegExp>

#include "libheat/components/border.h"

QVector<QVector<Border>> multiParse( QString src );
QVector<Border> parsePolygon(QString src);

Border parseBorder(QString st);

void dataChecker(const QVector<QVector<Border> > &data);
void onePolyCheck(const QVector<Border> &data);
void twoPolyCheck(const QVector<Border> & a, const QVector<Border> & b);

class ParseError
{
public:
	ParseError();
	ParseError(const QString &what, const QString & where = QString(""));

	const QString what() const noexcept;
	const QString where() const noexcept;

private:
	const QString m_what;
	const QString m_where;
};

namespace Parser
{
	const static QString m_floatToken = QString("[+-]?\\d*(\\.\\d+)?");
	const static QString m_pointToken = QString("\\(%1\\,\\s%1\\)").arg(m_floatToken);
	const static QString m_borderToken = QString("%1(\\s)*%1(\\s)*%2").arg(m_pointToken, m_floatToken);
}

#endif /* PARSER_H */
