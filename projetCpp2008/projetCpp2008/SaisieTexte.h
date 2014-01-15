#ifndef __SaisieTexte__
#define __SaisieTexte__

#include "Composant.h"

class SaisieTexte: public Composant{
private:
	bool isFocused;
	int cursorPos;
	string texte;
	int longueurMaxTexte;
	void (*changeFunction)(SaisieTexte*);
	void (*aChangeFunction)(SaisieTexte*);
public:
	SaisieTexte();
	SaisieTexte(const string name,Canvas* parent,Point position,
		int width,int bordure=0,
		const string texte=strdup(""),int longueurMaxTexte=0,
		int backgroundColor=0,int textColor=15,
		void (*changeAction)(SaisieTexte*)=NULL,
		void (*aChangeAction)(SaisieTexte*)=NULL);
	SaisieTexte(const SaisieTexte&);
	virtual ~SaisieTexte();
	string GetTexte()const;
	void SetTexte(const string);
	int GetLongeurMaxTexte()const;
	void SetLongueurMaxTexte(int);
	void SetFocus(bool);
	bool GetFocus()const;
	void SetCursorPos(int);
	int GetCursorPos()const;
	virtual bool isSaisieTexte()const{ return true; };
	void Afficher(ostream&)const;
	void actionKeyDown(COORD,char);
	void actionClick(COORD);
	void actionAChange(COORD);
	void actionChange(COORD);
	void focusSelected();
};
#endif