#include "ZoneDessin.h"
#include "Console.h"
#include<fstream>
#include<time.h>
#include<string>

#pragma warning(disable:4996)
#pragma warning(disable:4244)

ZoneDessin::ZoneDessin():Composant()
{
	this->couleur = 0;
	this->fichier = strdup("");
}
ZoneDessin::ZoneDessin(const string name,Canvas* parent,Point position,int width,int height,int bordure,int backgroundColor,int textColor,void(*actionClick)(ZoneDessin*),void(*actionClickMoved)(ZoneDessin*)):Composant(name,parent,position,width,height,bordure,backgroundColor,textColor)
{
	this->couleur = 0;
	this->clickFunction = actionClick;
	this->clickMovedFunction = actionClickMoved;
	int nb_aleatoire;
	srand(time(NULL));
	nb_aleatoire = rand()%(999999-1)+1;
	string nomFic = "C:\\Temp\\.tmpZoneDessin";
	char* nb_aleatoire_chaine=(char*)malloc(6*sizeof(char));
	sprintf(nb_aleatoire_chaine,"%d",nb_aleatoire);
	nomFic += nb_aleatoire_chaine;
	free(nb_aleatoire_chaine);
	this->fichier = nomFic;
	FILE* file;
	file = fopen(this->fichier.c_str(),"w+");
	if(file != NULL)
	{
		fclose(file);
	}
	else
	{
		cerr<<"Impossible d'ouvrir ou de creer le fichier"<<endl;
		exit(-1);
	}
}
ZoneDessin::ZoneDessin(const ZoneDessin& zd):Composant(zd)
{
	this->couleur = zd.couleur;
	this->clickFunction = zd.clickFunction;
	this->clickMovedFunction = zd.clickMovedFunction;
	this->fichier = zd.fichier;
}
ZoneDessin::~ZoneDessin()
{
	if( remove(this->fichier.c_str()) != 0 )
	{
		cerr<<"echec de la suppression du fichier temporaire"<<endl;
	}
}
int ZoneDessin::GetCouleur()const
{
	return this->couleur;
}
void ZoneDessin::SetCouleur(int coul)
{
	this->couleur = coul;
}
string ZoneDessin::GetFichier()const
{
	return this->fichier;
}
void ZoneDessin::actionClick(COORD c)
{
	if( clickFunction != NULL )
	{
		(*clickFunction)(this);
	}
	else
	{
		Console::gotoxy(c.X,c.Y);
		Console::setColor(this->couleur,this->couleur);
		cout<<" ";
		Sauvegarder(c,this->couleur);
		Console::setColor(7,0);
	}
}
void ZoneDessin::actionClickMoved(COORD c)
{
	if( clickMovedFunction != NULL )
	{
		(*clickMovedFunction)(this);
	}
	else
	{
		Console::gotoxy(c.X,c.Y);
		Console::setColor(this->couleur,this->couleur);
		cout<<" ";
		Sauvegarder(c,this->couleur);
		Console::setColor(7,0);
	}
}
bool ZoneDessin::Sauvegarder(COORD c,int couleur)const
{
	ofstream fichier(this->fichier.c_str(),ios::out | ios::app);
	fichier<<c.X-this->GetPosition()->GetX()<<" "<<c.Y-this->GetPosition()->GetY()<<" "<<couleur<<" "<<endl;
	fichier.close();
	return true;
}
bool ZoneDessin::Charger()const
{
	ifstream fichier(this->fichier.c_str(),ios::in);
	int indParseString,lastInd;
	string contenu;
	string contenuPart1,contenuPart2,contenuPart3;
	int indX,indY,color;
	if(fichier)
	{
		while( getline(fichier,contenu) )
		{
				indParseString = 0;
				while( contenu[indParseString] != ' ' )
				{
					indParseString++;
				}
				contenuPart1 = contenu.substr(0,indParseString);
				indX = atoi(contenuPart1.c_str());
				indParseString++;
				lastInd = indParseString;

				while( contenu[indParseString] != ' ' )
				{
					indParseString++;
				}
				contenuPart2 = contenu.substr(lastInd,indParseString);
				indY = atoi(contenuPart2.c_str());
				indParseString++;
				lastInd = indParseString;

				while( contenu[indParseString] != ' ' )
				{
					indParseString++;
				}
				contenuPart3 = contenu.substr(lastInd,indParseString);
				color = atoi(contenuPart3.c_str());
				Console::gotoxy(indX+this->GetPosition()->GetX(),indY+this->GetPosition()->GetY());
				Console::setColor(color,color);
				cout<<" ";
		}
		fichier.close();
		Console::setColor(7,0);
	}
	else
	{
		cerr<<"Impossible d'ouvrir le fichier"<<endl;
		return false;
	}
	return true;
}
bool ZoneDessin::Sauvegarder(const string path)const
{
	if( CopyFile((LPCSTR)this->fichier.c_str(),(LPCSTR)path.c_str(),true) )
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool ZoneDessin::Charger(const string path)const
{
	if( CopyFile((LPCSTR)path.c_str(),(LPCSTR)this->fichier.c_str(),true) )
	{
		return true;
	}
	else
	{
		return false;
	}
}
void ZoneDessin::Afficher(ostream& s)const
{
	Charger();
}