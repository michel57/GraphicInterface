#include "Point.h"

Point::Point()
{
	this->x=0;
	this->y=0;
}
Point::Point(int x,int y)
{
	this->x=x;
	this->y=y;
}
Point::Point(const Point& p)
{
	this->x=p.x;
	this->y=p.y;
}
Point::~Point()
{
}
int Point::GetX()const
{
	return this->x;
}
void Point::SetX(int x)
{
	this->x=x;
}
int Point::GetY()const
{
	return this->y;
}
void Point::SetY(int y)
{
	this->y=y;
}
Point Point::operator+(const Point& p)const
{
	return(Point(p.x+this->x,p.y+this->y));
}
Point Point::operator-(const Point& p)const
{
	return(Point(p.x-this->x,p.y-this->y));
}
bool Point::operator==(const Point& p)const
{
	return( p.x==this->x && p.y==this->y);
}
ostream& operator<<(ostream& s,Point& p)
{
	s<<"("<<p.x<<","<<p.y<<")";
	return s;
}