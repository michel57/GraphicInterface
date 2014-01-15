#ifndef __TitleBar__
#define __TitleBar__

#include "Canvas.h"

class TitleBar: public Canvas{
private:
	string title;
	int barColor;
	int titleColor;
	char closeIcon;
public:
	static const int HAUTEUR = 3;
	TitleBar();
	TitleBar(Canvas* parent,const string title,int barColor=0,int titleColor=0);
	TitleBar(const TitleBar&);
	virtual ~TitleBar();
	string GetTitle()const;
	void SetTitle(const string);
	int GetBarColor()const;
	void SetBarColor(int);
	int GetTitleColor()const;
	void SetTitleColor(int);
	char GetCloseIcon()const;
	void SetCloseIcon(char);
	int GetHauteur()const;
	friend ostream& operator<<(ostream&, const TitleBar&);

};
#endif