#ifndef __Image__
#define __Image__

#include "Composant.h"

class Image: public Composant{
private:
	string fichier;
	friend class Icone;
	Image(Point position,int width,int height,const string fichier,int bordure=0,int backgroundColor=0,int textColor=7);
public:
	Image();
	Image(const string name,Canvas* parent,Point position,int width,int height,const string fichier,int bordure=0,int backgroundColor=0,int textColor=7);
	Image(const Image&);
	virtual ~Image();
	string GetFichier()const;
	void SetFichier(const string);
	void Afficher(ostream&)const;
};
#endif