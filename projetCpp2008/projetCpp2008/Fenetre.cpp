#include "Fenetre.h"
#include "Console.h"
#include"Event.h"

#pragma warning(disable:4996)

Fenetre::Fenetre():Canvas()
{
	this->name = strdup("");
	this->titleBar = new TitleBar(this,"Calculatrice",7,9);
	this->SetBackgroundColor(0);
	this->groupe = new Groupe();
	this->groupe->SetParent(this);
	Event::AjouterFenetre(this);
}
Fenetre::Fenetre(const string name,const Point& position,
	const string title,int barColor,int titleColor,
	int width,int height,int bordure,int BackgroundColor,
	void(*actionClose)(Fenetre*),
	void(*actionMouseDown)(Fenetre*),void (*actionMouseUp)(Fenetre*),
	void (*actionMouseMove)(Fenetre*),void (*actionClick)(Fenetre*),
	void (*actionKeyDown)(Fenetre*)):
	Canvas(position,(width>9 )?width:10,(height>9)?height:10,bordure)
{
	this->name = name;
	this->closeFunction = actionClose;
	this->mouseDownFunction = actionMouseDown;
	this->mouseUpFunction = actionMouseUp;
	this->mouseMoveFunction = actionMouseMove;
	this->keyDownFunction = actionKeyDown;
	this->titleBar = new TitleBar(this,title,barColor,titleColor);
	//on écrit les parametres du groupe principal à la main car /= des autres groupes
	// (à cause de la barre title)
	this->groupe = new Groupe();
	this->groupe->SetParent(this);
	this->groupe->SetPosition(position.GetX(),position.GetY()+this->GetTitleBar()->GetHeight());
	this->groupe->SetWidth(width);
	this->groupe->SetHeight(height-this->GetTitleBar()->GetHeight());
	this->SetBackgroundColor(BackgroundColor);
	Event::AjouterFenetre(this);
}
Fenetre::~Fenetre()
{
	delete this->titleBar;
	delete this->groupe;
}
TitleBar* Fenetre::GetTitleBar()const
{
	return this->titleBar;
}
void Fenetre::SetTitleBar(TitleBar* t)
{
	this->titleBar = t;
}
Groupe* Fenetre::GetGroupe()const
{
	return this->groupe;
}
void Fenetre::SetGroupe(Groupe* g)
{
	this->groupe = g;
}
int Fenetre::GetBackgroundColor()const
{
	return this->GetGroupe()->GetBackgroundColor();
}
void Fenetre::SetBackgroundColor(int BackgroundColor)
{
	this->GetGroupe()->SetBackgroundColor(BackgroundColor);
}
string Fenetre::GetName()const
{
	return this->name;
}
void Fenetre::SetName(const string name)
{
	this->name = name;
}
void Fenetre::SetPosition(int x,int y)
{
	int difTaskBarHeight = 0;
	if( Event::GetTaskbar() != NULL )
	{
		difTaskBarHeight = 6;
	}
	if( this->GetPosition()->GetX()+x >= 0 && this->GetPosition()->GetX()+this->GetWidth() < Console::getWidth()-1
		&& this->GetPosition()->GetY()+y >= 0 && this->GetPosition()->GetY()+this->GetHeight() < Console::getHeight()-difTaskBarHeight )
	{
		Canvas::SetPosition(this->GetPosition()->GetX()+x,this->GetPosition()->GetY()+y);
		this->titleBar->SetPosition(this->titleBar->GetPosition()->GetX()+x,this->titleBar->GetPosition()->GetY()+y);
		this->groupe->SetPosition(this->groupe->GetPosition()->GetX()+x,this->groupe->GetPosition()->GetY()+y);
		for(int i=0;i<this->groupe->GetNbComposants();i++)
		{
			this->groupe->GetComposantAt(i)->SetPosition(this->groupe->GetComposantAt(i)->GetPosition()->GetX()+x,this->groupe->GetComposantAt(i)->GetPosition()->GetY()+y);
		}
	}
}
bool Fenetre::isCloseFunction()const
{
	if( this->closeFunction != NULL )
	{
		return true;
	}
	else
	{
		return false;
	}
}
Composant* Fenetre::GetComposantByName(const string name)const
{
	Composant* c;
	for(list<Composant*>::iterator i = groupe->GetListeComposants()->begin();i!=groupe->GetListeComposants()->end();++i)
	{
		if( (*i)->GetName() == name )
		{
			return *i;
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
void Fenetre::closeClick()
{
	if( closeFunction != NULL )
	{
		(*closeFunction)(this);
	}
}
void Fenetre::DessinerBordure()const
{
	for(int i=this->GetPosition()->GetX();i<this->GetPosition()->GetX()+this->GetWidth();i++)
	{
		for(int j=this->GetPosition()->GetY();j<this->GetPosition()->GetY()+this->GetHeight();j++)
		{
			
			Console::gotoxy(i,j);
			if( i == this->GetPosition()->GetX() && j == this->GetPosition()->GetY() )
			{
				/*Affichage du caractère ascii situé représentant le coin en haut à gauche du rectangle.*/
				if( this->GetBordure() == 1)
					cout<<"\xDA";
				else if(this->GetBordure() == 2)
					cout<<"\xC9";
			}
			else if( i > this->GetPosition()->GetX() && i < this->GetPosition()->GetX()+this->GetWidth()-1 && j == this->GetPosition()->GetY() )
			{
				/*Ligne du haut entre les 2 coins haut gauche et haut droite  */
				if( this->GetBordure() == 1)
					cout<<"\xC4";
				else if(this->GetBordure() == 2)
					cout<<"\xCD";
			}
			else if( i == this->GetPosition()->GetX()+this->GetWidth()-1 && j == this->GetPosition()->GetY() )
			{
				 //Affichage du caractère ascii situé représentant le coin en haut à droite du rectangle.
				if( this->GetBordure() == 1)
					cout<<"\xBF";
				else if(this->GetBordure() == 2)
					cout<<"\xBB";
			}
			else if( (i == this->GetPosition()->GetX() || i == this->GetPosition()->GetX()+this->GetWidth()-1) && j < this->GetPosition()->GetY()+this->GetHeight()-1 )
			{
				//verticales
				if( this->GetBordure() == 1)
					cout<<"\xB3";
				else if(this->GetBordure() == 2)
					cout<<"\xBA";
			}
			else if( i == this->GetPosition()->GetX() && j == this->GetPosition()->GetY()+this->GetHeight()-1 )
			{
				//coin bas gauche
				if( this->GetBordure() == 1)
					cout<<("\xC0"); 
				else if(this->GetBordure() == 2)
					cout<<"\xC8";
			}
			else if( i > this->GetPosition()->GetX() && i < this->GetPosition()->GetX()+this->GetWidth()-1 && j == this->GetPosition()->GetY()+this->GetHeight()-1 )
			{
				//ligne bas
				if( this->GetBordure() == 1)
					cout<<("\xC4");
				else if(this->GetBordure() == 2)
					cout<<"\xCD";
			}
			else if( i == this->GetPosition()->GetX()+this->GetWidth()-1 && j == this->GetPosition()->GetY()+this->GetHeight()-1 )
			{
				//coin bas droite
				if( this->GetBordure() == 1)
					cout<<("\xD9");
				else if(this->GetBordure() == 2)
					cout<<"\xBC";
			}
			else if( (i >this->GetPosition()->GetX() && i < this->GetPosition()->GetX()+this->GetWidth()-1) && j == this->GetPosition()->GetY()+this->GetTitleBar()->GetHauteur()-1 )
			{
				//separateur titre
				if( this->GetBordure() == 1)
					cout<<("\xC4");
				else if(this->GetBordure() == 2)
					cout<<"\xCD";
			}
			Console::gotoxy(i,j);
			if( i == this->GetPosition()->GetX() && j == this->GetPosition()->GetY()+this->GetTitleBar()->GetHauteur()-1 )
			{
				//separation gauche titlebar
				if( this->GetBordure() == 1)
					cout<<("\xC3");
				else if(this->GetBordure() == 2)
					cout<<"\xCC";
			}
			else if( i == this->GetPosition()->GetX()+this->GetWidth()-1 && j == this->GetPosition()->GetY()+this->GetTitleBar()->GetHauteur()-1 )
			{
				//separation droite titlebar
				if( this->GetBordure() == 1)
					cout<<("\xB4");
				else if(this->GetBordure() == 2)
					cout<<"\xB9";
			}
		}
	}
	Console::gotoxy(this->GetPosition()->GetX(),this->GetPosition()->GetY());
}
void Fenetre::AjouterComposant(Composant* composant)
{
	//on ajoute le composant au groupe
	this->GetGroupe()->AjouterComposant(composant);
}
void Fenetre::actionKeyDown(COORD mouseCoord,char c)
{
	if( this->keyDownFunction != NULL )
	{
		(*keyDownFunction)(this);
	}
}
void Fenetre::actionMouseMove(COORD c)
{
	if( this->mouseMoveFunction != NULL )
	{
		(*mouseMoveFunction)(this);
	}
}
void Fenetre::actionMouseDown(COORD c)
{
	if( this->mouseDownFunction != NULL )
	{
		(*mouseDownFunction)(this);
	}
}
void Fenetre::actionMouseUp(COORD c)
{
	if( this->mouseUpFunction != NULL )
	{
		(*mouseUpFunction)(this);
	}
}
void Fenetre::actionClickMoved(COORD c,COORD* deplacement)
{
	this->SetPosition(deplacement->X,deplacement->Y);
}
ostream& operator<<(ostream& s,const Fenetre& f)
{
	Console::setColor(7,0);
	//title bar
	s<<*(f.GetTitleBar());
	//placement du curseur sur la 1ere case (0,0)
	Console::gotoxy(f.GetPosition()->GetX()+1,f.GetPosition()->GetY()+f.GetTitleBar()->GetHauteur());
	//affichage du groupe principal qui enchaine tous les autres
	s<<*(f.GetGroupe());
	//bordure de fenetre
	f.DessinerBordure();
	return s;
}