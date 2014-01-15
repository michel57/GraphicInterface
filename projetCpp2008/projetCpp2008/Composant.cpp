#include "Composant.h"
#include "Console.h"
#include "Fenetre.h"
#include <stdexcept>

#pragma warning(disable:4996)

Composant::Composant():Canvas()
{
	this->name = strdup("");
	this->backgroundColor = 15;
	this->textColor = 7;
	this->parent = NULL;
}
Composant::Composant(const string name,Canvas* parent,
	Point position,
	int width,int height,
	int bordure,int backgroundColor,
	int textColor):Canvas((
	position.GetX()+parent->GetPosition()->GetX() < parent->GetPosition()->GetX()+parent->GetWidth() && 
	position.GetY()+parent->GetPosition()->GetY()+TitleBar::HAUTEUR+2 < parent->GetPosition()->GetY()+parent->GetHeight() )?
	Point(position.GetX()+parent->GetPosition()->GetX()+1,position.GetY()+parent->GetPosition()->GetY()+TitleBar::HAUTEUR):
	Point(parent->GetPosition()->GetX()+1,parent->GetPosition()->GetY()+TitleBar::HAUTEUR),
	(position.GetX()+parent->GetPosition()->GetX()+width+2 < parent->GetPosition()->GetX()+parent->GetWidth() )?
	width+2:
	width-((position.GetX()+parent->GetPosition()->GetX()+width+2)-(parent->GetPosition()->GetX()+parent->GetWidth())),
	(position.GetY()+parent->GetPosition()->GetY()+height+2 < parent->GetPosition()->GetY()+parent->GetHeight())?
	height+2:
	height+2-((position.GetY()+parent->GetPosition()->GetY()+height+2)-(parent->GetPosition()->GetY()+parent->GetHeight()))-TitleBar::HAUTEUR-1,
	bordure)
{
	this->name = name;
	if( backgroundColor < 0 || backgroundColor > 15 )
	{
		this->backgroundColor = 0;
	}
	else
	{
		this->backgroundColor = backgroundColor;
	}
	if( textColor < 0 || textColor > 15 )
	{
		this->textColor = textColor;
	}
	else
	{
		this->textColor = textColor;
	}
	this->parent = parent;
	if( this->parent->isFenetre() )
	{
		((Fenetre*)(this->parent))->AjouterComposant(this);
	}
	else
	{
		((Groupe*)(this->parent))->AjouterComposant(this);
	}
}
Composant::Composant(Point position,int width,int height,int bordure,int backgroundColor,int textColor):Canvas(Point(position.GetX(),position.GetY()+TitleBar::HAUTEUR-1),width+2,height+2,bordure)
{
	this->backgroundColor = backgroundColor;
	this->textColor = textColor;
}
Composant::Composant(const Composant& c):Canvas(c)
{
	this->backgroundColor = c.backgroundColor;
	this->textColor = c.textColor;
	this->parent = c.parent;
	if( parent != NULL )
	{
		((Fenetre*)(this->parent))->AjouterComposant(this);
	}
}
Composant::~Composant()
{
}
Canvas* Composant::GetParent()const
{
	return this->parent;
}
void Composant::SetParent(Canvas* parent)
{
	this->parent = parent;
}
int Composant::GetBackgroundColor()const
{
	return this->backgroundColor;
}
void Composant::SetBackgroundColor(int backgroundColor)
{
	this->backgroundColor = backgroundColor;
}
int Composant::GetTextColor()const
{
	return this->textColor;
}
void Composant::SetTextColor(int textColor)
{
	this->textColor = textColor;
}
string Composant::GetName()const
{
	return this->name;
}
void Composant::SetName(const string name)
{
	this->name = name;
}
void Composant::RemplirFond()const
{
	Console::setColor(this->GetBackgroundColor(),this->GetBackgroundColor());
	for(int i=this->GetPosition()->GetX();i<this->GetPosition()->GetX()+this->GetWidth();i++)
	{
		for(int j=this->GetPosition()->GetY();j<this->GetPosition()->GetY()+this->GetHeight();j++)
		{
			Console::gotoxy(i,j);
			cout<<" ";
		}
	}
	Console::setColor(7,0);
}
ostream& operator<<(ostream& s,const Composant& c)
{
	c.RemplirFond();
	c.DessinerBordure();
	c.Afficher(s);
	return s;
}