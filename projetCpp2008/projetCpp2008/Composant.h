#ifndef __Composant__
#define __Composant__

#include "Canvas.h"

class Composant: public Canvas{
private:
	Canvas* parent;
	int backgroundColor;
	int textColor;
	string name;
protected:
	Composant(Point position,int width,int height,int bordure,int backgroundColor=0,int textColor=15);
public:
	Composant();
	Composant(const string name,Canvas* parent,Point position,int width,int height,int bordure,int backgroundColor=0,int textColor=15);
	Composant(const Composant&);
	virtual ~Composant();
	Canvas* GetParent()const;
	void SetParent(Canvas*);
	int GetBackgroundColor()const;
	void SetBackgroundColor(int);
	int GetTextColor()const;
	void SetTextColor(int);
	string GetName()const;
	void SetName(const string);
	void RemplirFond()const;
	virtual bool isGroupe()const{ return false; };
	virtual bool isBouton()const{ return false; };
	virtual bool isSaisieTexte()const{ return false; };
	virtual void Afficher(ostream&)const{};
	friend ostream& operator<<(ostream&,const Composant&);
};
#endif