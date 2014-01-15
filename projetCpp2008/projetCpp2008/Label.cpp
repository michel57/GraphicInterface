#include "Label.h"
#include "Console.h"

#pragma warning(disable:4996)
#pragma warning(disable:4018)

Label::Label():Composant()
{
	this->contenu = "NULL";
}
Label::Label(const string name,Canvas* parent,Point position,int width,int height,int bordure,const string contenu,int backgroundColor,int textColor):Composant(name,parent,position,width,height,bordure,backgroundColor,textColor)
{
	this->contenu = contenu;
}
Label::Label(Point position,int width,int height,int bordure,const string contenu,int backgroundColor,int textColor):Composant(position,width,height,bordure,backgroundColor,textColor)
{
	this->contenu = contenu;
}
Label::Label(const Label& l):Composant(l)
{
	this->contenu = l.contenu;
}
Label::~Label()
{
}
string Label::GetContenu()const
{
	return this->contenu;
}
void Label::SetContenu(const string contenu)
{
	this->contenu = contenu;
}
void Label::Afficher(ostream& s)const
{
	int tailleContenu;
	Console::setColor(this->GetTextColor(),this->GetBackgroundColor());
	if( this->GetContenu().length() > this->GetWidth()-2 )
	{
		string tmp;
		tmp = this->GetContenu();
		tmp = tmp.substr(0,this->GetWidth()-3-2-1);
		tmp+="...";
		tailleContenu = tmp.length();
		Console::gotoxy(this->GetPosition()->GetX()+((this->GetWidth()-tailleContenu)/2),this->GetPosition()->GetY()+this->GetHeight()/2);
		s<<tmp.c_str();
	}
	else
	{
		tailleContenu = this->GetContenu().length();
		Console::gotoxy(this->GetPosition()->GetX()+((this->GetWidth()-tailleContenu)/2),this->GetPosition()->GetY()+this->GetHeight()/2);
		s<<this->GetContenu().c_str();
	}
	Console::setColor(7,0);
}