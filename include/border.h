#ifndef BORDER_H
#define BORDER_H

#include <iostream>

class Point
{
public:
    Point();
    Point(double x, double y);
    ~Point();

    double x();
    double y();

    friend std::ostream & operator<<(std::ostream & os, const Point & p);
    friend std::istream & operator>>(std::istream & is, Point & p);
private:
    double m_x, m_y;
};

class Border
{
public:
    Point();
    Point(double x, double y);
    ~Point();

    double x();
    double y();

    friend std::ostream & operator<<(std::ostream & os, const Point & p);
    friend std::istream & operator>>(std::istream & is, Point & p);
private:
    Point first, second;
    double u;
};


#endif // BORDER_H
