// -*- C++ -*-
/*
 */

/* 
 * File:   parser.h
 * Author: ivan
 *
 * Created on 7 апреля 2016 г., 20:33
 */

#ifndef PARSER_H
#define PARSER_H

struct Point
{
    double x, y;
};

struct Border
{
    Point first, second;
    double u;
};

#include <list>
#include <fstream>
#include <sstream>

std::list<Border> parseFile(const char * path);
Border parseLine(const std::string &st);

#endif /* PARSER_H */

