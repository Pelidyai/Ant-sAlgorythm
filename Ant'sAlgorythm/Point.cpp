#include "Point.h"
Point::Point()
{
	x = 0; y = 0;
}
Point::Point(double x, double y)
{
	this->x = x, this->y = y;
}
Point::Point(Point& base)
{
	this->x = base.x;
	this->y = base.y;
}