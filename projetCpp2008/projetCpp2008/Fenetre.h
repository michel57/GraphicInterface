#ifndef __Fenetre__
#define __Fenetre__

#include "TitleBar.h"
#include "Groupe.h"
#include "Canvas.h"
#include "Point.h"

class Fenetre: public Canvas{
private:
	TitleBar* titleBar;
	Groupe* groupe;
	string name;
	void (*mouseDownFunction)(Fenetre*);
	void (*mouseUpFunction)(Fenetre*);
	void (*mouseMoveFunction)(Fenetre*);
	void (*clickFunction)(Fenetre*);
	void (*keyDownFunction)(Fenetre*);
	void (*closeFunction)(Fenetre*);
public:
	Fenetre();
	Fenetre(const string name,const Point& position,
		const string title,int barColor,int titleColor,
		int width=0,int height=0,int bordure=0,
		int clientColor=0,void(*actionClose)(Fenetre*)=NULL,
		void(*actionMouseDown)(Fenetre*)=NULL,void (*actionMouseUp)(Fenetre*)=NULL,
		void (*actionMouseMove)(Fenetre*)=NULL,void (*actionClick)(Fenetre*)=NULL,
		void (*actionKeyDown)(Fenetre*)=NULL);
	virtual ~Fenetre();
	TitleBar* GetTitleBar()const;
	void SetTitleBar(TitleBar*);
	Groupe* GetGroupe()const;
	void SetGroupe(Groupe*);
	int GetBackgroundColor()const;
	void SetBackgroundColor(int);
	string GetName()const;
	void SetName(const string);
	void SetPosition(int,int);
	bool isCloseFunction()const;
	Composant* GetComposantByName(const string)const;
	virtual void DessinerBordure()const;
	virtual void AjouterComposant(Composant*);
	void closeClick();
	void actionKeyDown(COORD,char);
	void actionMouseMove(COORD);
	void actionMouseDown(COORD);
	void actionMouseUp(COORD);
	void actionClickMoved(COORD,COORD*);
	virtual bool isFenetre()const{ return true; };
	friend ostream& operator<<(ostream&,const Fenetre&);
	
};
#endif