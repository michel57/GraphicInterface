#include"Console.h"
#include"Event.h"

#include<iostream>

using namespace std;

#pragma warning(disable:4996)


// Fonction qui initialise la console et retourne un handle permettant de la gérer
// Ce handle devra être fourni à toutes les fonctions qui le demande
HANDLE Console::initConsole ()
{
	DWORD mode;

	// On récupère le handle de la console
	HANDLE in = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(in, &mode);
	// On active la capture des événements souris
	// On désactive le QUICK_EDIT_MODE et le INSERT_MODE
	SetConsoleMode(in, (mode | ENABLE_MOUSE_INPUT) & ~ENABLE_QUICK_EDIT_MODE & ~ENABLE_INSERT_MODE);

	return in;
}

// Fonction qui récupère un événement d'entrée de la console dont le handle est fourni
// Résultat true si un événement était disponible, false sinon
// in : handle de la console
// evt : événement lu (si résultat true)
bool Console::getEvent (HANDLE in, INPUT_RECORD * evt)
{
	DWORD nb;

	// on vérifie s'il y a au moins un événement à prendre
	GetNumberOfConsoleInputEvents (in, &nb);

	if (nb == 0)
		// aucun événement disponible
		return false;

	DWORD read;

	// on prend l'événement disponible
	ReadConsoleInput(in, evt, 1, &read);

	// un événement a été pris
	return true;
}

// Résultat true si l'événement est un événement clavier
bool Console::keybEvent (INPUT_RECORD evt)
{
	return (evt.EventType == KEY_EVENT);
}

// Retourne le caractère tapé avec evt un événement clavier
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

// Résultat true si l'événement est un événement souris
bool Console::mouseEvent (INPUT_RECORD evt)
{
	return (evt.EventType == MOUSE_EVENT);
}

// Retourne l'état des boutons de la souris avec evt un événement souris
DWORD Console::buttonMouseEvent (INPUT_RECORD evt)
{
	return (evt.Event.MouseEvent.dwButtonState);
}

// Retourne les coordonnées de la souris avec evt un événement souris
COORD Console::xyMouseEvent (INPUT_RECORD evt)
{
	return (evt.Event.MouseEvent.dwMousePosition);
}

//Retourne les coordonnées du curseur de la console
COORD Console::xyConsoleCursor (HANDLE h)
{
	CONSOLE_SCREEN_BUFFER_INFO conInfo;
	GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &conInfo );
	return( conInfo.dwCursorPosition );
}

// Programme test qui affiche les événements clavier et souris de la console
// en provenance de la Console
void Console::test ()
{
	bool fin = false;

	INPUT_RECORD go;

	HANDLE console = initConsole ();

	// on boucle jusqu'à appui sur la touche Echap
	do
	{
		// On prend un événement sur la console
		bool eventDisponible = getEvent (console, &go);

		// Y en avait-il un ?
		if (eventDisponible)
		{
			// Est-ce un événement clavier ?
			if (keybEvent (go))
			{
				// On récupère le caractère 
				CHAR c = charKeybEvent (go);
				// On l'affiche si c'est un caractère alpha-numérique
				if (isalpha (c))
				{
					gotoxy (0,0);
					printf ("clavier %c       ", c);
				}
				// On s'arrête si c'est la touche "Echap"
				fin = (c == 27);
			}
			// Est-ce un événement souris ?
			else if (mouseEvent (go))
			{
				// On récupère l'état des boutons
				DWORD button = buttonMouseEvent (go);
				// On récupère les coordonnées
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