#include "Event.h"
#include "Bouton.h"
#include<iostream>
#include "MouseEvent.h"
#include "SaisieTexte.h"

using namespace std;

bool Event::finProgramme = false;
list<Fenetre*> Event::objets;
list<Icone*> Event::icones;
TaskBar* Event::taskbar = NULL;

list<Fenetre*>* Event::GetObjets()
{
	return &(Event::objets);
}

void Event::AjouterFenetre(Fenetre* f)
{
	Event::objets.push_front(f);
}
void Event::SupprimerFenetre(Fenetre* f)
{
	int ind = -1,ind2 = -1;
	for(list<Fenetre*>::iterator i=Event::objets.begin();i!=Event::objets.end();++i)
	{
		ind++;
		if( (*i) == f )
		{
			Event::objets.remove(*i);
			delete f;
			break;
		}
	}
	if( taskbar != NULL )
	{
		int coordX;
		Bouton* bou;
		//on garde la coordonnee du bouton et on le supprime
		for(list<Bouton*>::iterator i=taskbar->GetListeBoutons()->begin();i!=taskbar->GetListeBoutons()->end();++i)
		{
			ind2++;
			if( ind2 == ind )
			{
				bou = *i;
				coordX = (*i)->GetPosition()->GetX();
				taskbar->GetListeBoutons()->remove(*i);
				delete bou;
				break;
			}
		}
		// on decale les boutons situes apres celui efface
		for(list<Bouton*>::iterator i = taskbar->GetListeBoutons()->begin();i!=taskbar->GetListeBoutons()->end();++i)
		{
			if( (*i)->GetPosition()->GetX() > coordX )
			{
				(*i)->GetPosition()->SetX( (*i)->GetPosition()->GetX() -10 );
			}
		}
		taskbar->SetNbBoutons(taskbar->GetNbBoutons()-1);
	}
}
void Event::PremierPlan(Fenetre* f)
{
	int ind = -1,ind2 = -1;
	Fenetre* fen;
	for(list<Fenetre*>::iterator i=Event::objets.begin();i!=Event::objets.end();++i)
	{
		ind++;
		if( (*i) == f )
		{
			fen = *i;
			Event::objets.remove(f);
			break;
		}
	}
	if( taskbar != NULL )
	{
		Bouton* b;
		int coordX;
		//on garde la coordonnee du bouton et on le supprime
		for(list<Bouton*>::iterator i=taskbar->GetListeBoutons()->begin();i!=taskbar->GetListeBoutons()->end();++i)
		{
			ind2++;
			if( ind2 == ind )
			{
				b = *i;
				coordX = b->GetPosition()->GetX();
				taskbar->GetListeBoutons()->remove(b);
				break;
			}
		}
	}
	Event::GetObjets()->push_front(fen);
}
bool Event::ParcourComposantClick(COORD mouseCoord)
{
	int noElement = -1;
	bool actionFaite = false;
	bool actionFaiteSansModif = false;
	//on parcours toutes les fenetres
	for (list<Fenetre*>::iterator courant=Event::objets.begin(); courant!=Event::objets.end(); courant++)
	{
		noElement++;
		//si on clique sur une fenetre
		if( mouseCoord.X > (*courant)->GetPosition()->GetX() && mouseCoord.X < (*courant)->GetPosition()->GetX()+(*courant)->GetWidth()
			&& mouseCoord.Y > (*courant)->GetPosition()->GetY() && mouseCoord.Y < (*courant)->GetPosition()->GetY()+(*courant)->GetHeight() )
		{
			//si ce n'est pas le premier element, on le passe devant et  on relance la fonction
			if( noElement != 0 )
			{
				Bouton* bou;
				if( taskbar != NULL )
				{
					int indBouton=-1;
					for(list<Bouton*>::iterator i=taskbar->GetListeBoutons()->begin();i!=taskbar->GetListeBoutons()->end();++i)
					{
						indBouton++;
						if( noElement == indBouton )
						{
							bou = *i;
							taskbar->GetListeBoutons()->remove(*i);
							break;
						}
					}
				}
				Event::PremierPlan(*courant);
				if( taskbar != NULL )
				{
					taskbar->GetListeBoutons()->push_front(bou);
				}
				Event::ParcourComposantClick(mouseCoord);
				actionFaite = true;
			}
			else
			{
				//si click pour fermer
				if( mouseCoord.X == (*courant)->GetPosition()->GetX()+(*courant)->GetTitleBar()->GetWidth()-2
					&& mouseCoord.Y == (*courant)->GetPosition()->GetY()+(*courant)->GetTitleBar()->GetHeight()/2 )
				{
					Fenetre* f=*courant;
					if( f->isCloseFunction() )
					{
						f->closeClick();
					}
					else
					{
						Event::SupprimerFenetre(f);
					}
					actionFaite = true;
				}
				//sinon
				else
				{
					list<Composant*> listeContenuGrp;
					Groupe* groupeCourant;
					//on parcours les composants de la fenetre
					for (int ind =0;ind<(*courant)->GetGroupe()->GetNbComposants();ind++)
					{
						if ( !((*courant)->GetGroupe()->GetComposantAt(ind)->isGroupe()) )
						{
							if ( (mouseCoord.X>=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetX()+1) && (mouseCoord.X<=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetX()+(*courant)->GetGroupe()->GetComposantAt(ind)->GetWidth()-2)
								&& (mouseCoord.Y>=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetY()+1) && (mouseCoord.Y<=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetY()+(*courant)->GetGroupe()->GetComposantAt(ind)->GetHeight()-2) )
							{
								(*courant)->GetGroupe()->GetComposantAt(ind)->actionClick(mouseCoord);
								actionFaiteSansModif=true;
								break;
							}
						}
						//c'est un groupe, parcours recursif des composants
						else
						{
							groupeCourant = ((Groupe*)((*courant)->GetGroupe()->GetComposantAt(ind)));
							for(int i=0;i<groupeCourant->GetNbComposants();i++)
							{
								listeContenuGrp.push_back(groupeCourant->GetComposantAt(i));
							}
							bool continuer;
							do{
								continuer = false;
								//pour tous les composants dans la liste
								for(list<Composant*>::iterator i=listeContenuGrp.begin();i!=listeContenuGrp.end();++i)
								{
									//si c'est un groupe, on le decompose en composants finaux et on vire le groupe de la liste
									if( (*i)->isGroupe() )
									{
										continuer = true;
										groupeCourant = ((Groupe*)((*i)));
										for(int j=0;j<groupeCourant->GetNbComposants();j++)
										{
											listeContenuGrp.push_back(groupeCourant->GetComposantAt(j));
										}
										listeContenuGrp.remove( (*i) );
									}
								}
							} while( continuer);
							//il reste que des composants hors groupes, il suffit de les parcourir
							for(list<Composant*>::iterator i=listeContenuGrp.begin();i!=listeContenuGrp.end();++i)
							{
								if ( (mouseCoord.X>=(*i)->GetPosition()->GetX()+1) && (mouseCoord.X<=(*i)->GetPosition()->GetX()+(*i)->GetWidth()-2)
								&& (mouseCoord.Y>=(*i)->GetPosition()->GetY()+1) && (mouseCoord.Y<=(*i)->GetPosition()->GetY()+(*i)->GetHeight()-2) )
								{
									(*i)->actionClick(mouseCoord);
									actionFaiteSansModif=true;
									break;
								}
							}
						}
					}
					//si clic dans fenetre active mais sur aucun composant
					if( !actionFaite && !actionFaiteSansModif )
					{
						if( mouseCoord.X > (*courant)->GetGroupe()->GetPosition()->GetX() && mouseCoord.X < (*courant)->GetGroupe()->GetPosition()->GetX()+(*courant)->GetGroupe()->GetWidth()-1
							&& mouseCoord.Y > (*courant)->GetGroupe()->GetPosition()->GetY()-1 && mouseCoord.Y < (*courant)->GetGroupe()->GetPosition()->GetY()+(*courant)->GetGroupe()->GetHeight()-1 )
						{	
							(*courant)->actionClick(mouseCoord);
						}
					}
					actionFaiteSansModif = true;
				}
			}
		}
		if( actionFaite )
		{
			Event::Afficher();
			return true;
		}
		if( actionFaiteSansModif )
		{
			return true;
		}
	}
	return false;
}
bool Event::ParcoursComposantClickMoved(COORD mouseCoord,COORD* deplacement)
{
	int noElement = -1;
	bool actionFaite = false;
	bool actionFaiteSansModif = false;
	//on parcours toutes les fenetres
	for (list<Fenetre*>::iterator courant=Event::objets.begin(); courant!=Event::objets.end(); courant++)
	{
		noElement++;
		//si on clique sur une fenetre
		if( mouseCoord.X > (*courant)->GetPosition()->GetX() && mouseCoord.X < (*courant)->GetPosition()->GetX()+(*courant)->GetWidth()
			&& mouseCoord.Y > (*courant)->GetPosition()->GetY() && mouseCoord.Y < (*courant)->GetPosition()->GetY()+(*courant)->GetHeight() )
		{
			//si ce n'est pas le premier element, on le passe devant et  on relance la fonction
			if( noElement != 0 )
			{
				Bouton* bou;
				if( taskbar != NULL )
				{
					int indBouton=-1;
					for(list<Bouton*>::iterator i=taskbar->GetListeBoutons()->begin();i!=taskbar->GetListeBoutons()->end();++i)
					{
						indBouton++;
						if( noElement == indBouton )
						{
							bou = *i;
							taskbar->GetListeBoutons()->remove(*i);
							break;
						}
					}
				}
				Event::PremierPlan(*courant);
				if( taskbar != NULL )
				{
					taskbar->GetListeBoutons()->push_front(bou);
				}
				Event::ParcoursComposantClickMoved(mouseCoord,deplacement);
				actionFaite = true;
			}
			else
			{
				if( mouseCoord.X >= (*courant)->GetPosition()->GetX()+1 && mouseCoord.X <= (*courant)->GetPosition()->GetX()+1+(*courant)->GetWidth()
					&& mouseCoord.Y >= (*courant)->GetPosition()->GetY()+1 && mouseCoord.Y <= (*courant)->GetPosition()->GetY()+1+TitleBar::HAUTEUR )
				{
					//deplacement fenetre
					(*courant)->actionClickMoved(mouseCoord,deplacement);
					actionFaiteSansModif = true;
					Event::Afficher();
				}
				else
				{
					//on parcours les composants de la fenetre
					for (int ind =0;ind<(*courant)->GetGroupe()->GetNbComposants();ind++)
					{
						if ( !((*courant)->GetGroupe()->GetComposantAt(ind)->isGroupe()) )
						{
							if ( (mouseCoord.X>=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetX()+1) && (mouseCoord.X<=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetX()+(*courant)->GetGroupe()->GetComposantAt(ind)->GetWidth()-2)
								&& (mouseCoord.Y>=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetY()+1) && (mouseCoord.Y<=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetY()+(*courant)->GetGroupe()->GetComposantAt(ind)->GetHeight()-2) )
							{
								(*courant)->GetGroupe()->GetComposantAt(ind)->actionClickMoved(mouseCoord);
								actionFaiteSansModif=true;
								break;
							}
						}
					}
					actionFaiteSansModif = true;
				}
			}
		}
		if( actionFaite )
		{
			Event::Afficher();
			return true;
		}
		if( actionFaiteSansModif )
		{
			return true;
		}
	}
	return false;
}
bool Event::ParcoursComposantKeyDown(COORD mouseCoord,char c)
{
	//fenetre au 1er plan
	list<Fenetre*>::iterator courant=Event::objets.begin();
	//on parcours les composants de la 1ere fenetre (au 1er plan)
	for (int ind =0;ind<(*courant)->GetGroupe()->GetNbComposants();ind++)
	{
		//si c'est un saisieTexte
		if( ((*courant)->GetGroupe()->GetComposantAt(ind)->isSaisieTexte()) )
		{
			if( ((SaisieTexte*)(*courant)->GetGroupe()->GetComposantAt(ind))->GetFocus() )
			{
				(*courant)->GetGroupe()->GetComposantAt(ind)->actionKeyDown(mouseCoord,c);
				return true;
			}
		}
		else
		{
			//si clic sur autre composant
			if ( (mouseCoord.X>=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetX()+1) && (mouseCoord.X<=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetX()+(*courant)->GetGroupe()->GetComposantAt(ind)->GetWidth()-2)
				&& (mouseCoord.Y>=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetY()+1) && (mouseCoord.Y<=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetY()+(*courant)->GetGroupe()->GetComposantAt(ind)->GetHeight()-2) )
			{	
				return false;
			}
		}
	}
	//si on est sur la zone client de la fenetre
	if( mouseCoord.X > (*courant)->GetGroupe()->GetPosition()->GetX() && mouseCoord.X < (*courant)->GetGroupe()->GetPosition()->GetX()+(*courant)->GetGroupe()->GetWidth()-1
		&& mouseCoord.Y > (*courant)->GetGroupe()->GetPosition()->GetY()-1 && mouseCoord.Y < (*courant)->GetGroupe()->GetPosition()->GetY()+(*courant)->GetGroupe()->GetHeight()-1 )
	{	
		(*courant)->actionKeyDown(mouseCoord,c);
		return true;
	}
	return false;
}
bool Event::ParcoursComposantMove(COORD mouseCoord)
{
	if( !Event::objets.empty() )
	{
		//fenetre au 1er plan
		list<Fenetre*>::iterator courant=Event::objets.begin();
		//si on est sur la zone client de la fenetre
		if( mouseCoord.X > (*courant)->GetGroupe()->GetPosition()->GetX() && mouseCoord.X < (*courant)->GetGroupe()->GetPosition()->GetX()+(*courant)->GetGroupe()->GetWidth()-1
			&& mouseCoord.Y > (*courant)->GetGroupe()->GetPosition()->GetY()-1 && mouseCoord.Y < (*courant)->GetGroupe()->GetPosition()->GetY()+(*courant)->GetGroupe()->GetHeight()-1 )
		{	
			//on parcours les composants de la 1ere fenetre (au 1er plan)
			for (int ind =0;ind<(*courant)->GetGroupe()->GetNbComposants();ind++)
			{
				//si ce n'est pas un groupe
				if ( !((*courant)->GetGroupe()->GetComposantAt(ind)->isGroupe()) )
				{
					//si on est dans un composant
					if ( (mouseCoord.X>=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetX()) && (mouseCoord.X<=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetX()+(*courant)->GetGroupe()->GetComposantAt(ind)->GetWidth()-3)
						&& (mouseCoord.Y>=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetY()) && (mouseCoord.Y<=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetY()+(*courant)->GetGroupe()->GetComposantAt(ind)->GetHeight()) )
					{
						return false;
					}
				}
				//si c'est un groupe, parcours recursif de ses composants
				else
				{
				}
			}
			(*courant)->actionMouseMove(mouseCoord);
			return true;
		}
		return false;
	}
	else
	{
		return false;
	}
}
bool Event::ParcoursComposantMouseDownOrUp(COORD mouseCoord,bool downOrUp)
{
	if( !Event::objets.empty() )
	{
		//fenetre au 1er plan
		list<Fenetre*>::iterator courant=Event::objets.begin();
		//si on est sur la zone client de la fenetre
		if( mouseCoord.X > (*courant)->GetGroupe()->GetPosition()->GetX() && mouseCoord.X < (*courant)->GetGroupe()->GetPosition()->GetX()+(*courant)->GetGroupe()->GetWidth()-1
			&& mouseCoord.Y > (*courant)->GetGroupe()->GetPosition()->GetY()-1 && mouseCoord.Y < (*courant)->GetGroupe()->GetPosition()->GetY()+(*courant)->GetGroupe()->GetHeight()-1 )
		{	
			//on parcours les composants de la 1ere fenetre (au 1er plan)
			int nbC = (*courant)->GetGroupe()->GetNbComposants();
			for (int ind =0;ind<(*courant)->GetGroupe()->GetNbComposants();ind++)
			{
				//si on est dans un composant
				if ( (mouseCoord.X>=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetX()+1) && (mouseCoord.X<=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetX()+(*courant)->GetGroupe()->GetComposantAt(ind)->GetWidth()-2)
								&& (mouseCoord.Y>=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetY()+1) && (mouseCoord.Y<=(*courant)->GetGroupe()->GetComposantAt(ind)->GetPosition()->GetY()+(*courant)->GetGroupe()->GetComposantAt(ind)->GetHeight()-2) )
				{	
					return false;
				}
			}
			if( downOrUp )
			{
				(*courant)->actionMouseDown(mouseCoord);
			}
			else
			{
				(*courant)->actionMouseUp(mouseCoord);
			}
			return true;
		}
		return false;
	}
	else
	{
		return false;
	}
}
void Event::AjouterIcone(Icone* i)
{
	Event::icones.push_back(i);
}
void Event::SupprimerIcone(Icone* ico)
{
	for(list<Icone*>::const_iterator i=Event::icones.begin();i!=Event::icones.end();++i)
	{
		if( (*i) == ico )
		{
			Event::icones.remove(ico);
			break;
		}
	}
}

void Event::ParcoursIcones(COORD mouseCoord)
{
	for(list<Icone*>::const_iterator i=icones.begin();i!=icones.end();++i)
	{
		if( mouseCoord.X > (*i)->GetPosition()->GetX() && mouseCoord.X < (*i)->GetPosition()->GetX()+(*i)->GetWidth()-1
			&& mouseCoord.Y > (*i)->GetPosition()->GetY() && mouseCoord.Y < (*i)->GetPosition()->GetY()+(*i)->GetHeight()-1 )
		{
			(*i)->actionClick();
		}
	}
}

void Event::AjouterTaskBar(TaskBar* t)
{
	taskbar = t;
}

void Event::SupprimerTaskBar()
{
	taskbar = NULL;
}
void Event::ParcoursTaskBar(COORD mouseCoord)
{
	int indBouton = -1;
	int indFenetre = -1;

	//si c'est dans la taskbar
	if( mouseCoord.X > taskbar->GetPosition()->GetX() && mouseCoord.X < taskbar->GetPosition()->GetX()+taskbar->GetWidth()-1
		&& mouseCoord.Y > taskbar->GetPosition()->GetY() && mouseCoord.Y < taskbar->GetPosition()->GetY()+taskbar->GetHeight()-1 )
	{
		//si c'est le bouton de fermeture
		if( mouseCoord.X > taskbar->GetFermeture()->GetPosition()->GetX() && mouseCoord.X < taskbar->GetFermeture()->GetPosition()->GetX()+taskbar->GetFermeture()->GetWidth()-1
			&& mouseCoord.Y > taskbar->GetFermeture()->GetPosition()->GetY() && mouseCoord.Y < taskbar->GetFermeture()->GetPosition()->GetY()+taskbar->GetFermeture()->GetHeight()-1 )
		{
			system("cls");
			cout<<"Extinction...";
			Event::Destructeur();
			Sleep(1500);
			finProgramme = true;
		}
		else
		{
			//sinon on parcours la liste des boutons
			for(list<Bouton*>::const_iterator i=taskbar->GetListeBoutons()->begin();i!=taskbar->GetListeBoutons()->end();++i)
			{
				indBouton++;
				//si on trouve un bouton correspondant aux coordonnees
				if( mouseCoord.X > (*i)->GetPosition()->GetX() && mouseCoord.X < (*i)->GetPosition()->GetX()+(*i)->GetWidth()-1
					&& mouseCoord.Y > (*i)->GetPosition()->GetY() && mouseCoord.Y < (*i)->GetPosition()->GetY()+(*i)->GetHeight()-1 )
				{
					//on met au 1er plan la fenetre correspondante
					for(list<Fenetre*>::iterator ind=objets.begin();ind!=objets.end();++ind)
					{
						indFenetre++;
						if( indBouton == indFenetre )
						{
							taskbar->PremierPlan((*ind));
							Event::Afficher();
							break;
						}
					}
					break;
				}
			}
		}
	}
}

void Event::ActiverEvenements()
{
	bool clicSurComposant = false;

	INPUT_RECORD go;

	HANDLE console = Console::initConsole ();
	MouseEvent Mouse;
	Mouse.SetMouseButtonPrev(0);
	COORD c;
	c.X=0; c.Y=0;
	COORD lastMousePosition;
	Mouse.SetMouseCoordPrev(c);

	// on boucle jusqu'à appui sur la touche Echap
	do
	{
		// On prend un événement sur la console
		bool eventDisponible = Console::getEvent (console, &go);

		// Y en avait-il un ?
		if (eventDisponible)
		{
			// Est-ce un événement clavier ?
			if (Console::keybEvent (go))
			{
				// On récupère le caractère
				CHAR c = Console::charKeybEvent (go);
				if( c != -1 )
				{
					Event::ParcoursComposantKeyDown(lastMousePosition,c);
				}
			}
			// Est-ce un événement souris ?
			else if (Console::mouseEvent (go))
			{
				// On récupère l'état des boutons
				DWORD button = Console::buttonMouseEvent (go);
				// On récupère les coordonnées
				lastMousePosition = Console::xyMouseEvent(go);
				COORD coord =  Console::xyMouseEvent(go);
				bool mouseDownZoneClient = false;
				Event::ParcoursComposantMove(coord);
				if ( Mouse.MouseDown(console,go) )
				{ 
					allFocusOFF();
					mouseDownZoneClient = Event::ParcoursComposantMouseDownOrUp(coord,true);
				}
				if( Mouse.MouseUp(console,go) )
				{
					allFocusOFF();
					mouseDownZoneClient = Event::ParcoursComposantMouseDownOrUp(coord,false);
				}
				if( !mouseDownZoneClient )
				{
					COORD deplacement;
					deplacement.X = 0;
					deplacement.Y = 0;
					if ( Mouse.MouseClickMoved(console,go,&deplacement) )
					{
						Event::ParcoursComposantClickMoved(coord,&deplacement);
					}
					else if ( Mouse.MouseClick(console,go) )
					{
						allFocusOFF();
						clicSurComposant = Event::ParcourComposantClick(coord);
						if( clicSurComposant == false )
						{
							Event::ParcoursIcones(coord);
						}
						else
						{
							clicSurComposant = false;
						}
						if( Event::taskbar != NULL )
						{
							Event::ParcoursTaskBar(coord);
						}
					}
				}
			}
		}
	}
	while (!Event::finProgramme);
}
void Event::AfficherFenetres()
{
	for(list<Fenetre*>::reverse_iterator i = Event::GetObjets()->rbegin();i!=Event::GetObjets()->rend();++i)
	{
		cout<<(**i);
	}
}
void Event::AfficherIcones()
{
	for(list<Icone*>::iterator i = Event::icones.begin();i!=Event::icones.end();++i)
	{
		cout<<(**i);
	}
}
void Event::Afficher()
{
	Console::viderConsole();
	Event::AfficherIcones();
	if( taskbar != NULL )
	{
		cout<<*taskbar;
	}
	else
	{
		Event::AfficherFenetres();
	}
}
void Event::Destructeur()
{
	Fenetre* f;
	list<Fenetre*>::iterator i;
	while( ! objets.empty() )
	{
		i = objets.begin();
		f = *i;
		objets.remove(*i);
		delete f;
	}
	while( !icones.empty() )
	{
		icones.pop_front();
	}
}
TaskBar* Event::GetTaskbar()
{
	return taskbar;
}
Fenetre* Event::GetFenetreByName(const string nom)
{
	Fenetre* f;
	for(list<Fenetre*>::iterator i = objets.begin();i!=objets.end();++i)
	{
		f = *i;
		if( f->GetName() == nom )
		{
			return f;
		}
	}
	return NULL;
}
void Event::allFocusOFF()
{
		//mise a faux de tous les focus saisieTexte
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
		Console::showCursor(false);
}