#include "Icone.h"
#include "Console.h"
#include "Fenetre.h"
#include "Event.h"

#pragma warning(disable:4996)

Icone::Icone():Canvas()
{
	this->img = NULL;
	this->lbl = NULL;
	Event::AjouterIcone(this);
}
Icone::Icone(Point position,const char* lienImageIcone,const char* label,int bordure,void(*actionClick)(Icone*)):Canvas(Point(position.GetX()+1,position.GetY()+1),8,6,bordure)
{
	this->img = new Image(Point(position.GetX()+1+1,position.GetY()-1),this->GetImgWidth(),this->GetImgHeight(),lienImageIcone,0,0,7);
	if( strlen(label) > 6 )
	{
		string tmp;
		tmp = label;
		tmp = tmp.substr(0,2);
		tmp+="...";
		this->lbl = new Label(Point(position.GetX()+1,position.GetY()-1+this->GetImgHeight()+1),6,1,0,tmp.c_str(),0,7);
	}
	else
	{
		this->lbl = new Label(Point(position.GetX()+1,position.GetY()-1+this->GetImgHeight()+1),6,1,0,label,0,7);
	}
	this->clickFunction = actionClick;
	Event::AjouterIcone(this);
}
Icone::Icone(const Icone& i):Canvas(i)
{
	this->img = new Image(*i.img);
	this->lbl = new Label(*i.lbl);
	this->clickFunction = i.clickFunction;
	Event::AjouterIcone(this);
}
Icone::~Icone()
{
	Event::SupprimerIcone(this);
	delete this->img;
	delete this->lbl;
}
Image* Icone::GetImg()const
{
	return this->img;
}
void Icone::SetImg(Image* i)
{
	this->img = i;
}
Label* Icone::GetLbl()const
{
	return this->lbl;
}
void Icone::SetLbl(Label* l)
{
	this->lbl = l;
}
void Icone::actionClick()
{
	(*clickFunction)(this);
}
ostream& operator<<(ostream& s, const Icone& i)
{
	Console::gotoxy(i.GetPosition()->GetX(),i.GetPosition()->GetY());
	Console::setColor(7,0);
	s<<*i.img;
	s<<*i.lbl;
	Console::setColor(7,0);
	i.DessinerBordure();
	return s;
}
