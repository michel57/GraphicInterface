#ifndef __Canvas__
#define __Canvas__

#include "Point.h"
#include<Windows.h>

class Canvas{
private:
	Point* position;
	int width;
	int height;
	int bordure;
	Canvas* parent;
public:
	Canvas();
	Canvas(const Point& position,int width=0,int height=0,int styleBordure=0);
	Canvas(const Canvas&);
	virtual ~Canvas();
	Point* GetPosition()const;
	virtual void SetPosition(int,int);
	void SetPosition(const Point&);
	int GetBordure()const;
	void SetBordure(int);
	int GetWidth()const;
	void SetWidth(int);
	int GetHeight()const;
	void SetHeight(int);
	Canvas* GetParent()const;
	void SetParent(Canvas*);
	virtual void DessinerBordure()const;
	virtual void actionClick(COORD){};
	virtual void actionClickMoved(COORD){};
	virtual void actionKeyDown(COORD,char){};
	virtual void actionMouseMove(COORD){};
	virtual void actionMouseDown(COORD){};
	virtual void actionMouseUp(COORD){};
	virtual bool isFenetre()const{ return false; };
	friend ostream& operator<<(ostream&, const Canvas&);
};
#endif