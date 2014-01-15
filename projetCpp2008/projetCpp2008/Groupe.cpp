#include "Groupe.h"
#include "Console.h"
#include "Bouton.h"
#include "Image.h"
#include "Label.h"
#include "SaisieTexte.h"

#pragma warning(disable:4018)

Groupe::Groupe():Composant()
{
}
Groupe::Groupe(const string name,Canvas* parent,Point position,int width,int height,int bordure,int backgroundColor):Composant(name,parent,position,(width>0)?width:1,(height>0)?height:1,bordure,backgroundColor)
{
}
Groupe::~Groupe()
{
	Composant* c;
	list<Composant*>::iterator i;
	while( ! listeComposants.empty() )
	{
		i = listeComposants.begin();
		c = *i;
		listeComposants.remove(*i);
		delete c;
	}
}
void Groupe::AjouterComposant(Composant* composant)
{
	//on met le pere comment etant le groupe
	composant->SetParent(this);
	//on ajoute le composant au groupe
	this->listeComposants.push_back(composant);
}
void Groupe::SupprimerComposant(Composant* composant)
{
	this->listeComposants.remove(composant);
}
int Groupe::GetNbComposants()const
{
	return this->listeComposants.size();
}
Composant* Groupe::GetComposantAt(int position)const
{
	if( position >= this->listeComposants.size() )
	{
		return NULL;
	}
	else
	{
		int pos = -1;
		for(list<Composant*>::const_iterator i = this->listeComposants.begin();i!=this->listeComposants.end();++i)
		{
			pos++;
			if( pos == position )
			{
				return (*i);
			}
		}
		return NULL;
	}
}
list<Composant*>* Groupe::GetListeComposants()
{
	return &(this->listeComposants);
}
Composant* Groupe::GetComposantByName(const string name)const
{
	Composant* c;
	for(list<Composant*>::const_iterator i = listeComposants.begin();i!=listeComposants.end();++i)
	{
		if( (*i)->GetName().compare(name) )
		{
			return (*i);
		}
		if( (*i)->isGroupe() )
		{
			c = ((Groupe*)(*i))->GetComposantByName(name);
			if( c != NULL )
			{
				return c;
			}
		}
	}
	return NULL;
}
ostream& operator<<(ostream& s,const Groupe& g)
{
	g.RemplirFond();
	Console::setColor(7,0);
	Console::gotoxy(0,0);
	for(list<Composant*>::const_iterator i=g.listeComposants.begin();i!=g.listeComposants.end();++i)
	{
		s<<(**i);
	}
	return s;
}