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

QVector<Border> parsePlainText(QString src);

Border parseLine(QString st);

void dataChecker(const QVector<Border> &data);

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

#endif /* PARSER_H */
