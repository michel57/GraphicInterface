#include "SaisieTexte.h"
#include "Console.h"
#include "MouseEvent.h"
#include "Event.h"
#include <string.h>

#define D 4D
#define G 4B

#pragma warning(disable:4018)
#pragma warning(disable:4996)

SaisieTexte::SaisieTexte():Composant()
{
	this->texte = strdup("");
	this->longueurMaxTexte = 0;
	this->isFocused = false;
	this->cursorPos = -1;
}
SaisieTexte::SaisieTexte(const string name,Canvas* parent,Point position,
	int width,int bordure,const string texte,int longueurMaxTexte,
	int backgroundColor,int textColor,void (*changeAction)(SaisieTexte*),
	void (*aChangeAction)(SaisieTexte*)):
	Composant(name,parent,position,width,1,bordure,backgroundColor,textColor)
{
	if( longueurMaxTexte < texte.length() )
	{
		throw;
	}
	else if( longueurMaxTexte > width || texte.length() >width )
	{
		throw;
	}
	else
	{
		this->texte = texte;
		this->longueurMaxTexte = longueurMaxTexte;
		for(int i=this->texte.size();i<this->longueurMaxTexte;i++)
		{
			this->texte += " ";
		}
		this->changeFunction = changeAction;
		this->aChangeFunction = aChangeAction;
		this->isFocused = false;
		this->cursorPos = -1;
	}
}
SaisieTexte::SaisieTexte(const SaisieTexte& s):Composant(s)
{
	this->texte = s.texte;
	this->longueurMaxTexte = s.longueurMaxTexte;
	this->changeFunction = s.changeFunction;
	this->aChangeFunction = s.aChangeFunction;
	this->isFocused = s.isFocused;
	this->cursorPos = s.cursorPos;
}
SaisieTexte::~SaisieTexte()
{
}
string SaisieTexte::GetTexte()const
{
	return this->texte;
}
void SaisieTexte::SetTexte(const string texte)
{
	this->texte = texte;
}
int SaisieTexte::GetLongeurMaxTexte()const
{
	return this->longueurMaxTexte;
}
void SaisieTexte::SetLongueurMaxTexte(int longueurMaxTexte)
{
	this->longueurMaxTexte = longueurMaxTexte;
}
void SaisieTexte::SetFocus(bool focus)
{
	this->isFocused = focus;
}
bool SaisieTexte::GetFocus()const
{
	return this->isFocused;
}
void SaisieTexte::SetCursorPos(int cur)
{
	this->cursorPos = cur;
}
int SaisieTexte::GetCursorPos()const
{
	return this->cursorPos;
}
void SaisieTexte::actionKeyDown(COORD mouseCoord,char c)
{
	if( this->GetFocus() )
	{
		if( GetKeyState(VK_LEFT) & 32768 )
		{
			if( this->cursorPos > 0 )
			{
				this->cursorPos-=1;
				Console::gotoxy(this->GetPosition()->GetX()+cursorPos+1,this->GetPosition()->GetY()+1);
			}
		}
		else if( GetKeyState(VK_RIGHT) & 32768 )
		{
			if( this->cursorPos < this->longueurMaxTexte-1 )
			{
				this->cursorPos+=1;
				Console::gotoxy(this->GetPosition()->GetX()+cursorPos+1,this->GetPosition()->GetY()+1);
			}
		}
		else
		{
			if( this->cursorPos < this->longueurMaxTexte )
			{
				actionChange(mouseCoord);
				this->texte[this->cursorPos] = c;
				Console::setColor(this->GetTextColor(),this->GetBackgroundColor());
				cout<<c;
				this->cursorPos+=1;
				if( this->cursorPos == this->longueurMaxTexte )
				{
					Console::gotoxy(this->GetPosition()->GetX()+cursorPos,this->GetPosition()->GetY()+1);
				}
				actionAChange(mouseCoord);
			}
		}
	}
}
void SaisieTexte::Afficher(ostream& s)const
{
	Console::gotoxy(this->GetPosition()->GetX()+1,this->GetPosition()->GetY()+this->GetHeight()/2);
	Console::setColor(this->GetTextColor(),this->GetBackgroundColor());
	s<<this->GetTexte().c_str();
	for(int i=0;i<this->GetLongeurMaxTexte();i++)
	{
		if( this->GetTexte().at(i) == ' ' )
		{
			Console::gotoxy(this->GetPosition()->GetX()+i+1,this->GetPosition()->GetY()+1);
			Console::setColor(this->GetTextColor(),this->GetBackgroundColor());
			s<<"_";
		}
	}
	Console::setColor(7,0);
}
void SaisieTexte::actionClick(COORD mouseCoord)
{
	focusSelected();
	Console::gotoxy(mouseCoord.X,mouseCoord.Y);
	Console::showCursor(true);
	this->cursorPos = mouseCoord.X-this->GetPosition()->GetX()-1;
}
void SaisieTexte::focusSelected()
{
	//on parcours toutes les fenetres
	for (list<Fenetre*>::iterator courant=Event::GetObjets()->begin(); courant!=Event::GetObjets()->end(); courant++)
	{
		//on parcours les composants de la fenetre
		for (int ind =0;ind<(*courant)->GetGroupe()->GetNbComposants();ind++)
		{
			if ( ((*courant)->GetGroupe()->GetComposantAt(ind)->isSaisieTexte()) )
			{
				((SaisieTexte*)((*courant)->GetGroupe()->GetComposantAt(ind)))->SetFocus(false);
			}
		}
	}
	this->isFocused = true;
}
void SaisieTexte::actionAChange(COORD)
{
	if( this->aChangeFunction != NULL )
	{
		(*aChangeFunction)(this);
	}
}
void SaisieTexte::actionChange(COORD)
{
	if( this->changeFunction != NULL )
	{
		(*changeFunction)(this);
	}
}