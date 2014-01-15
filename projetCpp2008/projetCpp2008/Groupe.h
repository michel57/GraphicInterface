#include "Composant.h"
#include<list>

class Groupe: public Composant{
private:
	list<Composant*> listeComposants;
public:
	Groupe();
	Groupe(const string name,Canvas* parent,Point position,int width,int height,int bordure=0,int backgroundColor=7);
	virtual ~Groupe();
	void AjouterComposant(Composant*);
	void SupprimerComposant(Composant*);
	int GetNbComposants()const;
	list<Composant*>* GetListeComposants();
	Composant* GetComposantAt(int)const;
	Composant* GetComposantByName(const string name)const;
	virtual bool isGroupe()const{ return true; };
	friend ostream& operator<<(ostream&,const Groupe&);
};
