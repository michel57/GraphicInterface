#include "Image.h"
#include "Console.h"
#include<fstream>
#include<string>

#pragma warning(disable:4996)
#pragma warning(disable:4018)

Image::Image():Composant()
{
	this->fichier = strdup("");
}
Image::Image(const string name,Canvas* parent,Point position,int width,int height,const string fichier,int bordure,int backgroundColor,int textColor):Composant(name,parent,position,(width>0)?width:1,(height>0)?height:1,bordure,backgroundColor,textColor)
{
	this->fichier = fichier;
}
Image::Image(Point position,int width,int height,const string fichier,int bordure,int backgroundColor,int textColor):Composant(position,width,height,bordure,backgroundColor,textColor)
{
	this->fichier = fichier;
}
Image::Image(const Image& i)
{
	this->fichier = i.fichier;
}
Image::~Image()
{
}
string Image::GetFichier()const
{
	return this->fichier;
}
void Image::SetFichier(const string fichier)
{
	this->fichier = fichier;
}
void Image::Afficher(ostream& s)const
{
	int compteurH= 0;
	ifstream fichier(this->fichier.c_str(),ios::in);
	if(fichier)
	{
		string contenu;
		int ind = 0;
		while( getline(fichier,contenu) && compteurH <= this->GetHeight()-3 )
		{
			compteurH++;
			Console::gotoxy(this->GetPosition()->GetX()+1,this->GetPosition()->GetY()+ind+1);
			Console::setColor(this->GetTextColor(),this->GetBackgroundColor());
			ind++;
			if( contenu.length() > this->GetWidth()-2 )
			{
				contenu = contenu.substr(0,this->GetWidth()-2);
			}
			s<<contenu<<endl;
		}
	}
	else
	{
		cerr<<"Impossible de lire le fichier"<<endl;
	}
	Console::setColor(7,0);
}