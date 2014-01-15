#ifndef __Console__
#define __Console__

#include <windows.h>
#include <stdio.h>
#include <conio.h>

class Console{
public:
	static void gotoxy(int x, int y);
	static HANDLE initConsole ();
	static bool getEvent (HANDLE in, INPUT_RECORD * evt);
	static bool keybEvent (INPUT_RECORD evt);
	static CHAR charKeybEvent (INPUT_RECORD evt);
	static bool mouseEvent (INPUT_RECORD evt);
	static DWORD buttonMouseEvent (INPUT_RECORD evt);
	static COORD xyMouseEvent (INPUT_RECORD evt);
	static COORD xyConsoleCursor (HANDLE h);
	static void test ();
	static void showCursor(bool);
	static void setColor(int textColor,int backgroundColor);
	static void setSize(int width,int height);
	static int getWidth();
	static int getHeight();
	static void viderConsole();
};

#endif