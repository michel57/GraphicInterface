#ifndef __Label__
#define __Label__

#include "Composant.h"
class Label: public Composant{
private:
	string contenu;
	friend class TaskBar;
	friend class Icone;
	Label(Point position,int width,int height,int bordure=0,const string contenu=strdup(""),int backgroundColor=0,int textColor=7);
public:
	Label();
	Label(const string name,Canvas* parent,Point position,int width,int height,int bordure=0,const string contenu=strdup(""),int backgroundColor=0,int textColor=7);
	Label(const Label&);
	virtual ~Label();
	string GetContenu()const;
	void SetContenu(const string);
	void Afficher(ostream&)const;
};
#endif
