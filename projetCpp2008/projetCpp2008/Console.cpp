#include"Console.h"
#include"Event.h"

#include<iostream>

using namespace std;

#pragma warning(disable:4996)


// Fonction qui initialise la console et retourne un handle permettant de la g�rer
// Ce handle devra �tre fourni � toutes les fonctions qui le demande
HANDLE Console::initConsole ()
{
	DWORD mode;

	// On r�cup�re le handle de la console
	HANDLE in = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(in, &mode);
	// On active la capture des �v�nements souris
	// On d�sactive le QUICK_EDIT_MODE et le INSERT_MODE
	SetConsoleMode(in, (mode | ENABLE_MOUSE_INPUT) & ~ENABLE_QUICK_EDIT_MODE & ~ENABLE_INSERT_MODE);

	return in;
}

// Fonction qui r�cup�re un �v�nement d'entr�e de la console dont le handle est fourni
// R�sultat true si un �v�nement �tait disponible, false sinon
// in : handle de la console
// evt : �v�nement lu (si r�sultat true)
bool Console::getEvent (HANDLE in, INPUT_RECORD * evt)
{
	DWORD nb;

	// on v�rifie s'il y a au moins un �v�nement � prendre
	GetNumberOfConsoleInputEvents (in, &nb);

	if (nb == 0)
		// aucun �v�nement disponible
		return false;

	DWORD read;

	// on prend l'�v�nement disponible
	ReadConsoleInput(in, evt, 1, &read);

	// un �v�nement a �t� pris
	return true;
}

// R�sultat true si l'�v�nement est un �v�nement clavier
bool Console::keybEvent (INPUT_RECORD evt)
{
	return (evt.EventType == KEY_EVENT);
}

// Retourne le caract�re tap� avec evt un �v�nement clavier
CHAR Console::charKeybEvent (INPUT_RECORD evt)
{
	if( !evt.Event.KeyEvent.bKeyDown )
	{
		return -1;
	}
	else
	{
		return (evt.Event.KeyEvent.uChar.AsciiChar);
	}
}

// R�sultat true si l'�v�nement est un �v�nement souris
bool Console::mouseEvent (INPUT_RECORD evt)
{
	return (evt.EventType == MOUSE_EVENT);
}

// Retourne l'�tat des boutons de la souris avec evt un �v�nement souris
DWORD Console::buttonMouseEvent (INPUT_RECORD evt)
{
	return (evt.Event.MouseEvent.dwButtonState);
}

// Retourne les coordonn�es de la souris avec evt un �v�nement souris
COORD Console::xyMouseEvent (INPUT_RECORD evt)
{
	return (evt.Event.MouseEvent.dwMousePosition);
}

//Retourne les coordonn�es du curseur de la console
COORD Console::xyConsoleCursor (HANDLE h)
{
	CONSOLE_SCREEN_BUFFER_INFO conInfo;
	GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &conInfo );
	return( conInfo.dwCursorPosition );
}

// Programme test qui affiche les �v�nements clavier et souris de la console
// en provenance de la Console
void Console::test ()
{
	bool fin = false;

	INPUT_RECORD go;

	HANDLE console = initConsole ();

	// on boucle jusqu'� appui sur la touche Echap
	do
	{
		// On prend un �v�nement sur la console
		bool eventDisponible = getEvent (console, &go);

		// Y en avait-il un ?
		if (eventDisponible)
		{
			// Est-ce un �v�nement clavier ?
			if (keybEvent (go))
			{
				// On r�cup�re le caract�re 
				CHAR c = charKeybEvent (go);
				// On l'affiche si c'est un caract�re alpha-num�rique
				if (isalpha (c))
				{
					gotoxy (0,0);
					printf ("clavier %c       ", c);
				}
				// On s'arr�te si c'est la touche "Echap"
				fin = (c == 27);
			}
			// Est-ce un �v�nement souris ?
			else if (mouseEvent (go))
			{
				// On r�cup�re l'�tat des boutons
				DWORD button = buttonMouseEvent (go);
				// On r�cup�re les coordonn�es
				COORD coord =  xyMouseEvent (go);
				// On l'affiche
				gotoxy (0,0);
				printf ("souris %2u %2d %2d", button, coord.X, coord.Y);
			}
		}
	}
	while (!fin);
}

void Console::showCursor(bool choix)
{
	HANDLE hConsoleOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 10;
	cursorInfo.bVisible = choix;
	SetConsoleCursorInfo(hConsoleOuput,&cursorInfo);
}

void Console::gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;

	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

void Console::setColor(int textColor, int backgroundColor)
{
	HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(H,backgroundColor*16+textColor);
}

/*
	0 noir
	1 bleu fonce
	2 vert fonce
	3 turquoise
	4 rouge fonce
	5 violet
	6 vert
	7 gris clair
	8 gris fonce
	9 bleu fluo
	10 vert fluo
	11 turquoise
	12 rouge fluo
	13 violet 2
	14 jaune
	15 blanc
	*/

void Console::setSize(int width,int height)
{
	TaskBar* t;
	char* widthC=(char*)malloc(24*sizeof(char));
	char* heightC=(char*)malloc(24*sizeof(char));
	sprintf(widthC,"mode con cols=%d",width);
	sprintf(heightC,"mode con lines=%d",height);
	system(widthC);
	system(heightC);
    free(widthC);
    free(heightC);
	t = Event::GetTaskbar();
	if( t != NULL )
	{
		t = new TaskBar();
	}
}

int Console::getWidth()
{
	_CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
	return (info.dwSize.X);
}

int Console::getHeight()
{
	_CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
	return (info.dwSize.Y);
}

void Console::viderConsole()
{
	system("cls");
	initConsole();
}