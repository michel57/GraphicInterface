#include "TitleBar.h"
#include "Console.h"
#include "Composant.h"

#pragma warning(disable:4244)
#pragma warning(disable:4355)
#pragma warning(disable:4996)

TitleBar::TitleBar():Canvas()
{
	this->SetParent(NULL);
	this->title ="Nouvelle Fenetre";
	this->barColor = 0;
	this->titleColor = 0;
	this->closeIcon = 'X';
}
TitleBar::TitleBar(Canvas* parent,const string title,int barColor,int titleColor):Canvas(Point(*parent->GetPosition()),parent->GetWidth(),HAUTEUR)
{
	this->SetParent(parent);
	this->title = title;
	this->barColor = barColor;
	this->titleColor = titleColor;
	this->closeIcon = 'X';
}
TitleBar::TitleBar(const TitleBar& tb):Canvas(tb)
{
	this->SetParent(tb.GetParent());
	this->title = tb.title;
	this->barColor = tb.barColor;
	this->titleColor = tb.titleColor;
	this->closeIcon = tb.closeIcon;
}
TitleBar::~TitleBar()
{
}
string TitleBar::GetTitle()const
{
	return this->title;
}
void TitleBar::SetTitle(const string title)
{
	this->title = title;
}
int TitleBar::GetBarColor()const
{
	return this->barColor;
}
void TitleBar::SetBarColor(int barColor)
{
	this->barColor = barColor;
}
int TitleBar::GetTitleColor()const
{
	return this->titleColor;
}
void TitleBar::SetTitleColor(int titleColor)
{
	this->titleColor = titleColor;
}
char TitleBar::GetCloseIcon()const
{
	return this->closeIcon;
}
void TitleBar::SetCloseIcon(char closeIcon)
{
	this->closeIcon = closeIcon;
}
int TitleBar::GetHauteur()const
{
	return HAUTEUR;
}
ostream& operator<<(ostream& s, const TitleBar& t)
{
	Console::setColor(t.GetBarColor(),t.GetBarColor());
	for(int i=t.GetPosition()->GetX();i<t.GetPosition()->GetX()+t.GetWidth();i++)
	{
		for(int j=t.GetPosition()->GetY();j<t.GetPosition()->GetY()+t.GetHeight();j++)
		{
			Console::gotoxy(i,j);
			cout<<" ";
		}
	}
	Console::gotoxy(t.GetPosition()->GetX()+2,t.GetPosition()->GetY()+1);
	Console::setColor(t.GetTitleColor(),t.GetBarColor());
	if( t.GetTitle().length() > (t.GetWidth()*0.8)-1 )
	{
		string titre;
		titre = t.GetTitle();
		titre = titre.substr(0,(t.GetWidth()*0.8-3-1-1));
		titre+="...";
		s<<titre.c_str();
	}
	else
	{
		s<<t.GetTitle().c_str();
	}
	Console::gotoxy(t.GetPosition()->GetX()+t.GetWidth()-2,t.GetPosition()->GetY()+t.GetHeight()/2);
	Console::setColor(15,12);
	s<<t.GetCloseIcon();
	Console::setColor(7,0);
	return s;
}
