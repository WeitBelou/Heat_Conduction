#ifndef BORDER_H
#define BORDER_H

#include <iostream>

class Point
{
public:
    Point();
    Point(double x, double y);
    ~Point();

    double x() const;
    double y() const;

    friend std::ostream &operator<<(std::ostream &os, const Point &p);
    friend std::istream &operator>>(std::istream &is, Point &p);
private:
    double m_x, m_y;
};

class Border
{
public:
    Border();
    Border(Point first, Point second, double u);
    ~Border();

    const Point first() const;
    const Point second() const;
    double u() const;

    friend std::ostream &operator<<(std::ostream &os, const Border &b);
    friend std::istream &operator>>(std::istream &is, Border &b);
private:
    Point m_first, m_second;
    double m_u;
};


#endif // BORDER_H
