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
	ParseError(const QString &what, const int where = -1);

	const QString what() const noexcept;
	int where() const noexcept;

private:
	const QString m_what;
	const int m_where;
};

#endif /* PARSER_H */
