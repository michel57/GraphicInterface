#include "Bouton.h"
#include "Console.h"
#include "MouseEvent.h"

#pragma warning(disable:4018)
#pragma warning(disable:4996)

Bouton::Bouton():Composant()
{
	this->enfonce = false;
	this->nom = "Default";
	this->name = strdup("");
}
Bouton::Bouton(const string name,Canvas* parent,Point position,int width,int height,int bordure,const string nom,int backgroundColor,int textColor,void(*actionClick)(Bouton*)):Composant(name,parent,position,(width>0)?width:1,(height>0)?height:1,bordure,backgroundColor,textColor)
{
	this->enfonce = false;
	this->nom = nom;
	this->name = name;
	this->clickFunction = actionClick;
}
Bouton::Bouton(Point position,int width,int height,int bordure,const string nom,int backgroundColor,int textColor,void(*actionClick)(Bouton*)):Composant(position,width,height,bordure,backgroundColor,textColor)
{
	this->enfonce = false;
	this->nom = nom;
	this->name = strdup("");
	this->clickFunction = actionClick;
}
Bouton::Bouton(const Bouton& b):Composant(b)
{
	this->enfonce = b.enfonce;
	this->nom = b.GetNom();
	this->clickFunction = b.clickFunction;
}
Bouton::~Bouton()
{
}
bool Bouton::GetEnfonce()const
{
	return this->enfonce;
}
void Bouton::SetEnfonce(bool enfonce)
{
	this->enfonce = enfonce;
}
string Bouton::GetNom()const
{
	return this->nom;
}
void Bouton::SetNom(const string nom)
{
	this->nom = nom;
}
void Bouton::actionClick(COORD c)
{
	if( clickFunction != NULL )
	{
		(*clickFunction)(this);
	}
}
void Bouton::Afficher(ostream& s)const
{
	int tailleNom = strlen(this->GetNom().c_str());
	Console::setColor(this->GetTextColor(),this->GetBackgroundColor());
	string nom;
	if( this->GetNom().length() > this->GetWidth()-2 )
	{
		nom = this->GetNom();
		nom = nom.substr(0,this->GetWidth()-2-3);
		nom+="...";
	}
	else
	{
		nom = this->GetNom();
	}
	Console::gotoxy(this->GetPosition()->GetX()+((this->GetWidth()-nom.length())/2),this->GetPosition()->GetY()+this->GetHeight()/2);
	s<<nom;
	Console::setColor(7,0);
}