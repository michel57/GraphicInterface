#ifndef __Event__
#define __Event__

#include<string>
#include "Fenetre.h"
#include "Console.h"
#include <list>
#include "Icone.h"
#include "TaskBar.h"

using namespace std;

class Event
{
private:
	static list<Fenetre*> objets;
	static list<Icone*> icones;
	static TaskBar* taskbar;
	static bool ParcourComposantClick(COORD);
	static bool ParcoursComposantClickMoved(COORD,COORD*);
	static bool ParcoursComposantKeyDown(COORD,char);
	static bool ParcoursComposantMove(COORD);
	static bool ParcoursComposantMouseDownOrUp(COORD,bool);
	friend class Fenetre;
	static void AjouterFenetre(Fenetre*);
	static void PremierPlan(Fenetre*);
	friend class Icone;
	static void AjouterIcone(Icone*);
	static void SupprimerIcone(Icone*);
	static void ParcoursIcones(COORD);
	friend class TaskBar;
	static void AjouterTaskBar(TaskBar*);
	static void SupprimerTaskBar();
	static void ParcoursTaskBar(COORD);
	static void AfficherFenetres();
	static void AfficherIcones();
	static void Destructeur();
	static void allFocusOFF();
public:
	static bool finProgramme;
	static list<Fenetre*>* GetObjets();
	static void ActiverEvenements();
	static Fenetre* GetFenetreByName(const string);
	static void SupprimerFenetre(Fenetre*);
	static TaskBar* GetTaskbar();
	static void Afficher();
};

#endif