#ifndef __Bouton__
#define __Bouton__

#include "Composant.h"

class Bouton: public Composant{
private:
	bool enfonce;
	//nom du bouton
	string name;
	//contenu du bouton
	string nom;
	void (*clickFunction)(Bouton*);
	friend class TaskBar;
	Bouton(Point position,int width,int height,int bordure=0,const string nom="Bouton",int backgroundColor=0,int textColor=7,void(*clickAction)(Bouton*)=NULL);
public:
	Bouton();
	Bouton(const string name,Canvas* parent,Point position,
		int width,int height,int bordure=0,const string nom="Bouton",
		int backgroundColor=0,int textColor=7,void(*clickAction)(Bouton*)=NULL);
	Bouton(const Bouton&);
	virtual ~Bouton();
	bool GetEnfonce()const;
	void SetEnfonce(bool);
	string GetNom()const;
	void SetNom(const string);
	void actionClick(COORD);
	virtual bool isBouton()const{ return true; };
	void Afficher(ostream&)const;
};
#endif