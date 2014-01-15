#include "TaskBar.h"
#include "Console.h"
#include "Bouton.h"
#include "Event.h"

#pragma warning(disable:4996)

TaskBar::TaskBar():Canvas(Point(0,Console::getHeight()-6),Console::getWidth(),5,1)
{
	this->nbBoutons = 0;
	this->fermeture = new Bouton(Point(1,this->GetPosition()->GetY()-1),1,1,1,"X");
	Event::AjouterTaskBar(this);
}
TaskBar::~TaskBar()
{
	list<Bouton*>::iterator i;
	Bouton* b;
	while( ! listeBoutons.empty() )
	{
		i = listeBoutons.begin();
		b = *i;
		listeBoutons.remove(*i);
		delete b;
	}
	delete this->fermeture;
}
void TaskBar::AjouterFenetre(Fenetre* f)
{
	if( this->nbBoutons < 4 )
	{
		string nomBouton;
		if( f->GetTitleBar()->GetTitle().length() > 8 )
		{
			nomBouton = f->GetTitleBar()->GetTitle();
			nomBouton = nomBouton.substr(0,f->GetWidth()-3-2-1);
			nomBouton+="...";
		}
		else
		{
			nomBouton = f->GetTitleBar()->GetTitle();
		}

		this->listeBoutons.push_front(new Bouton(Point(5+(this->nbBoutons*10),this->GetPosition()->GetY()-1),8,1,1,nomBouton.c_str()));
		this->nbBoutons = this->nbBoutons+1;
		cout<<*this;
	}
}
void TaskBar::PremierPlan(Fenetre* f)
{
	int ind=-1,ind2=-1;
	for(list<Fenetre*>::iterator i = Event::GetObjets()->begin(); i!=Event::GetObjets()->end();++i)
	{
		ind++;
		if( (*i) == f )
		{
			Fenetre* fen = *i;
			Event::GetObjets()->remove(f);
			Event::GetObjets()->push_front(fen);
			break;
		}
	}
	for(list<Bouton*>::iterator i = listeBoutons.begin();i!=listeBoutons.end();++i)
	{
		ind2++;
		if( ind == ind2 )
		{
			Bouton* bou = *i;
			listeBoutons.remove(*i);
			listeBoutons.push_front(bou);
			break;
		}
	}
}
Bouton* TaskBar::GetFermeture()const
{
	return this->fermeture;
}
Fenetre* TaskBar::GetFenetreByName(const string name)const
{
	return Event::GetFenetreByName(name);
}
list<Bouton*>* TaskBar::GetListeBoutons()
{
	return &(this->listeBoutons);
}
int TaskBar::GetNbBoutons()const
{
	return this->nbBoutons;
}
void TaskBar::SetNbBoutons(int nbBoutons)
{
	this->nbBoutons = nbBoutons;
}
ostream& operator<<(ostream& s,const TaskBar& t)
{
	Console::setColor(7,0);
	s<<*t.fermeture;
	for(list<Fenetre*>::reverse_iterator i = Event::GetObjets()->rbegin();i!=Event::GetObjets()->rend();++i)
	{
		s<<(**i);
	}
	for(list<Bouton*>::const_iterator i = t.listeBoutons.begin();i!=t.listeBoutons.end();++i)
	{
		s<<(**i);
	}
	t.DessinerBordure();
	Console::setColor(7,0);
	return s;
}