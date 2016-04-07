/*
 */

#include "../include/parser.h"

using namespace std;

std::list<Border> parseFile(const char * path)
{
    ifstream file(path);
    
    list<Border> lst;

    while (file) {
        string s;
        getline(file, s);
        lst.push_back(parseLine(s));
    }

    file.close();

    return lst;
}

Border parseLine(const string & st)
{
    Border b;
    char ch;

    stringstream str(st);

    str >> ch;
    str >> b.first.x;
    str >> ch;
    str >> ch;
    str >> b.first.y;
    str >> ch;

    str >> ch;

    str >> ch;
    str >> b.first.x;
    str >> ch;
    str >> ch;
    str >> b.first.y;
    str >> ch;

    str >> ch;

    str >> b.u;

    return b;
}
