#ifndef __ZoneDessin__
#define __ZoneDessin__

#include "Composant.h"

class ZoneDessin: public Composant{
private:
	int couleur;
	void (*clickFunction)(ZoneDessin*);
	void (*clickMovedFunction)(ZoneDessin*);
	string fichier;
	bool Sauvegarder(COORD c,int couleur)const;
	bool Charger()const;
public:
	ZoneDessin();
	ZoneDessin(const string name,Canvas* parent,Point position,int width,int height,int bordure=0,int backgroundColor=0,int textColor=15,void(*actionClick)(ZoneDessin*)=NULL,void(*actionClickMoved)(ZoneDessin*)=NULL);
	ZoneDessin(const ZoneDessin&);
	virtual ~ZoneDessin();
	int GetCouleur()const;
	void SetCouleur(int);
	string GetFichier()const;
	void actionClick(COORD);
	void actionClickMoved(COORD);
	bool Sauvegarder(const string)const;
	bool Charger(const string)const;
	void Afficher(ostream&)const;
};
#endif