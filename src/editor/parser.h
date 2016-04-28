/*
 * File:   parser.h
 * Author: ivan
 *
 * Created on 7 апреля 2016 г., 20:33
 */

#ifndef PARSER_H
#define PARSER_H

#include <QVector>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QRegExp>

#include "../core/border.h"

QVector<QVector<Border>> MultiParse( QString src );
QVector<Border> parsePlainText(QString src);

Border parseBorder(QString st);

void dataChecker(const QVector<QVector<Border> > &data);
void onePolyCheck(const QVector<Border> &data);
void twoPolyCheck(const QVector<Border> & a, const QVector<Border> & b);

class ParseError
{
public:
	ParseError();
	ParseError(const QString &what, const QString & where = QString("Nowhere"));

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
