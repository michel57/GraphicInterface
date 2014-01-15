#ifndef __TaskBar__
#define __TaskBar__

#include<list>
#include "Bouton.h"
#include "Fenetre.h"

/* Si on utilise une taskBar, on doit ajouter toutes les fenetres
	dans la taskBar.
	L'affichage se fait simplement avec un affichage de la taskbar qui contient
	la liste de toutes les fenetres.
	*/
class TaskBar:public Canvas{
private:
	Bouton* fermeture;
	list<Bouton*> listeBoutons; // pour afficher les boutons
	int nbBoutons;
	friend class Event;
	void SetNbBoutons(int);
public:
	TaskBar();
	virtual ~TaskBar();
	void AjouterFenetre(Fenetre*);
	void PremierPlan(Fenetre*);
	Bouton* GetFermeture()const;
	Fenetre* GetFenetreByName(const string)const;
	list<Bouton*>* GetListeBoutons();
	int GetNbBoutons()const;
	friend ostream& operator<<(ostream&,const TaskBar&);
};
#endif