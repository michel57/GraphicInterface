#include "MouseEvent.h"

void MouseEvent::SetMouseButtonPrev(const DWORD& d)
{
	this->MouseButtonPrev=d;
}

void MouseEvent::SetMouseCoordPrev(const COORD& c)
{
	this->MouseCoordPrev=c;
}

DWORD MouseEvent::GetMouseButtonPrev()const
{
	return this->MouseButtonPrev;
}

COORD MouseEvent::GetMouseCoordPrev()const
{
	return this->MouseCoordPrev;
}
bool MouseEvent::MouseClick(HANDLE console, INPUT_RECORD evt)
{
	DWORD button = Console::buttonMouseEvent(evt);	// contient l'état des buttons aprés le passage de l'évenement
	COORD MouseCoordPrevMouseUp=this->GetMouseCoordPrev();	// contient les coordonnées de la souris lors du MouseDown
	if (MouseUp(console,evt))
	{
		// On vérifie si les coordonnées acutel sont égal à celle enregistré lors du MouseDown
		if ( (MouseCoordPrevMouseUp.X==Console::xyMouseEvent(evt).X) && (MouseCoordPrevMouseUp.Y==Console::xyMouseEvent(evt).Y) )
		{
			this->SetMouseCoordPrev(Console::xyMouseEvent(evt));	// on sauvegarde l'état souris
			this->SetMouseButtonPrev(Console::buttonMouseEvent (evt));
			return true;
		}
		else return false;
	}
	else return false;
}

// *******************  MouseClickMoved  *****************

bool MouseEvent::MouseClickMoved(HANDLE console, INPUT_RECORD evt,COORD* deplacement)
{
	DWORD button = Console::buttonMouseEvent(evt);	// contient l'état des buttons aprés le passage de l'évenement
	if( this->GetMouseButtonPrev() == button && button == 1 && (this->GetMouseCoordPrev().X != Console::xyMouseEvent(evt).X || this->GetMouseCoordPrev().Y != Console::xyMouseEvent(evt).Y) )
	{
		deplacement->X = Console::xyMouseEvent(evt).X-this->GetMouseCoordPrev().X;
		deplacement->Y = Console::xyMouseEvent(evt).Y-this->GetMouseCoordPrev().Y;
		this->SetMouseCoordPrev(Console::xyMouseEvent(evt));	// on sauvegarde l'état souris
		this->SetMouseButtonPrev(Console::buttonMouseEvent (evt));
		return true;
	}
	deplacement = NULL;
	return false;
}

// *******************  MouseDown  *****************

bool MouseEvent::MouseDown(HANDLE console, INPUT_RECORD evt)
{
	// On récupère l'etat courant des boutons
	DWORD button = Console::buttonMouseEvent (evt);
	// Si le bouton precedent est 0 (pas de clique) et que le bouton courant est 1 (clique gauche)
	if ( (button==1) && (this->GetMouseButtonPrev()==0) )
	{
		this->SetMouseCoordPrev(Console::xyMouseEvent(evt));
		this->SetMouseButtonPrev(button);
		return true;
	}
	else return false;
}

// *******************  MouseUp  *****************

bool MouseEvent::MouseUp(HANDLE console, INPUT_RECORD evt)
{
	// On récupère l'etat courant des boutons
	DWORD button = Console::buttonMouseEvent(evt);
	if ( (button==0) && (this->GetMouseButtonPrev()==1) )
	{
		return true;
	}
	else return false;
}