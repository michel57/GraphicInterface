#ifndef __Point__
#define __Point__

#include<iostream>

using namespace std;

class Point{
private:
	int x;
	int y;
public:
	Point();
	Point(int,int);
	Point(const Point&);
	virtual ~Point();
	int GetX()const;
	void SetX(int);
	int GetY()const;
	void SetY(int);
	Point operator+(const Point&)const;
	Point operator-(const Point&)const;
	bool operator==(const Point&)const;
	friend ostream& operator<<(ostream&,Point&);
};

#endif