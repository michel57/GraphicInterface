#ifndef __MouseEvent__
#define __MouseEvent__

#include<string>
#include "Composant.h"
#include "Console.h"

using namespace std;

class MouseEvent{
private:
	DWORD MouseButtonPrev;
	COORD MouseCoordPrev;
public:
	void SetMouseButtonPrev(const DWORD&);
	void SetMouseCoordPrev(const COORD&);
	DWORD GetMouseButtonPrev()const;
	COORD GetMouseCoordPrev()const;

	bool MouseClickMoved(HANDLE, INPUT_RECORD,COORD*);
	bool MouseClick(HANDLE, INPUT_RECORD);
	bool MouseDown(HANDLE, INPUT_RECORD);
	bool MouseUp(HANDLE, INPUT_RECORD);
};
#endif

