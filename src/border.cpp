#include "include/border.h"


Point::Point()
{
    m_x = m_y = 0;
}

Point::Point(double x, double y)
{
    m_x = x;
    m_y = y;
}

Point::~Point()
{

}

double Point::x()
{
    return m_x;
}

double Point::y()
{
    return m_y;
}

std::ostream &operator<<(std::ostream &os, const Point &p)
{
    os << "(" << x() << ", " << y() << ")";
    return os;
}

std::istream &operator>>(std::istream &is, Point &p)
{
    char ch;

    is >> ch >> m_x >> ch >> m_y >> ch; // (d, d)

    return is;
}

/******************************************************************************/

Border::Border()
{
    m_first = Point();
    m_second = Point();

    m_u = 0;
}

Border::Border(Point first, Point second, double u)
{
    m_first = first;
    m_second = second;
    m_u = u;
}

const Point Border::first()
{
    return m_first;
}

const Point Border::second()
{
    return m_second;
}

double Border::u()
{
    return m_u;
}

std::ostream &operator<<(std::ostream &os, const Border &b)
{
    os << b.first() << " " << b.second() << " " << b.u();
    return os;
}

std::istream &operator>>(std::istream &is, Border &b)
{
    is >> b.m_first << b.m_second << b.m_u;
    return is;
}
