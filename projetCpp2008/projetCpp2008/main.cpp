#include "Canvas.h"
#include "TaskBar.h"
#include "Icone.h"
#include "TitleBar.h"
#include "Fenetre.h"
#include "Bouton.h"
#include "Label.h"
#include "Console.h"
#include "SaisieTexte.h"
#include "Image.h"
#include "ZoneDessin.h"
#include "Event.h"
#include <Math.h>

#pragma warning(disable:4996)

void Calculatrice(TaskBar*);
void Dessin(TaskBar*);
void Test(TaskBar*);

void OuvrirCal(Icone*);
void OuvrirDessin(Icone*);
void OuvrirTest(Icone*);

void Nombre(Bouton*);
void Operateur(Bouton*);
void Total(Bouton*);
void RazNombre(Bouton*);
void Virgule(Bouton*);

void CouleurPinceau(Bouton*);
void SauvegarderDessin(Bouton*);
void ChargerDessin(Bouton*);

void SupprimerCalculatrice(Fenetre*);
void SupprimerDessin(Fenetre*);
void SupprimerTest(Fenetre*);

char oper[1];
double res = 0;
double nbEnCours = 0;
bool isDecimal = false;
int digitNum = 1;

int main()
{
//on change le titre
system("title Michel Fake OS Professional Edition");
//on masque le curseur
Console::showCursor(false);
//on agrandi la fenetre
Console::setSize(100,40);
//on cree la taskBar
TaskBar t;

//on cree les icones
Icone iCal(Point(0,0),"E:\\iconeCal.txt","Calc",1,OuvrirCal);
Icone iDraw(Point(0,6),"E:\\iconeDessin.txt","Draw",1,OuvrirDessin);
Icone iTest(Point(0,12),"E:\\iconeTest.txt","Test",1,OuvrirTest);

Event::Afficher();
Event::ActiverEvenements();

return 0;
}
void OuvrirCal(Icone* i)
{
	Calculatrice(Event::GetTaskbar());
}
void OuvrirTest(Icone* i)
{
	Test(Event::GetTaskbar());
}
void OuvrirDessin(Icone* i)
{
	Dessin(Event::GetTaskbar());
}
void Calculatrice(TaskBar* t)
{
	//fenetre principale de la calculatrice
	Fenetre* f = new Fenetre("calc",Point(15,1),"Calculatrice",1,15,23,25,2,1,SupprimerCalculatrice);
	//label de resultat contenu dans la fenetre
	Label* l= new Label("total",f,Point(1,1),12,1,1,"0.00",15,9);
	//boutons contenus dans la fenetre
	new Bouton("div",f,Point(16,1),2,1,1,"/",15,9,Operateur);
	new Bouton("sept",f,Point(1,5),2,1,1,"7",15,9,Nombre);
	new Bouton("huit",f,Point(6,5),2,1,1,"8",15,9,Nombre);
	new Bouton("neuf",f,Point(11,5),2,1,1,"9",15,9,Nombre);
	new Bouton("fois",f,Point(16,5),2,1,1,"x",15,9,Operateur);
	new Bouton("quatre",f,Point(1,9),2,1,1,"4",15,9,Nombre);
	new Bouton("cinq",f,Point(6,9),2,1,1,"5",15,9,Nombre);
	new Bouton("six",f,Point(11,9),2,1,1,"6",15,9,Nombre);
	new Bouton("moins",f,Point(16,9),2,1,1,"-",15,9,Operateur);
	new Bouton("un",f,Point(1,13),2,1,1,"1",15,9,Nombre);
	new Bouton("deux",f,Point(6,13),2,1,1,"2",15,9,Nombre);
	new Bouton("trois",f,Point(11,13),2,1,1,"3",15,9,Nombre);
	new Bouton("plus",f,Point(16,13),2,1,1,"+",15,9,Operateur);
	new Bouton("zero",f,Point(1,17),2,1,1,"0",15,9,Nombre);
	new Bouton("virgule",f,Point(6,17),2,1,1,",",15,9,Virgule);
	new Bouton("suppr",f,Point(11,17),2,1,1,"c",15,9,RazNombre);
	new Bouton("egal",f,Point(16,17),2,1,1,"=",15,9,Total);
	t->AjouterFenetre(f);
}
void Nombre(Bouton* b)
{
	if( isDecimal )
	{
		nbEnCours = nbEnCours+( atof(b->GetNom().c_str())/(pow(10.0,digitNum)) );
		digitNum++;
	}
	else
	{
		nbEnCours = nbEnCours*10+atoi(b->GetNom().c_str());
	}
	char result[255];
	sprintf(result,"%.2f",nbEnCours);
	((Label*)(Event::GetTaskbar()->GetFenetreByName("calc")->GetComposantByName("total")))->SetContenu(result);
	cout<<*Event::GetTaskbar()->GetFenetreByName("calc")->GetComposantByName("total");
}
void Virgule(Bouton* b)
{
	isDecimal = true;
}
void Operateur(Bouton* b)
{
	oper[0] = b->GetNom()[0];
	res = nbEnCours;
	nbEnCours = 0;
	isDecimal = false;
	digitNum = 1;
}
void RazNombre(Bouton* b)
{
	nbEnCours = 0;
	res = 0;
	oper[0] = ' ';
	isDecimal = false;
	digitNum = 1;
	char result[255];
	sprintf(result,"%.2f",nbEnCours);
	((Label*)(Event::GetTaskbar()->GetFenetreByName("calc")->GetComposantByName("total")))->SetContenu(result);
	cout<<*Event::GetTaskbar()->GetFenetreByName("calc")->GetComposantByName("total");
}
void Total(Bouton* b)
{
	switch (oper[0])
	{
		case '+': res+=nbEnCours; break;
		case '-': res-=nbEnCours; break;
		case 'x': res*=nbEnCours; break;
		case '/': res/=nbEnCours; break;
		default: break;
	}
	nbEnCours = res;
	char result[255];
	sprintf(result,"%.2f",nbEnCours);
	((Label*)(Event::GetTaskbar()->GetFenetreByName("calc")->GetComposantByName("total")))->SetContenu(result);
	cout<<*Event::GetTaskbar()->GetFenetreByName("calc")->GetComposantByName("total");
}
void Test(TaskBar* t)
{
	Fenetre* f2 = new Fenetre("test",Point(23,1),"Tests",1,15,50,24,2,0,SupprimerTest);
	new SaisieTexte("saisie",f2,Point(1,0),9,0,"test",9);
	new Image("img",f2,Point(1,2),41,16,"E:\\imageAsciiDemo.txt",1);
	t->AjouterFenetre(f2);
}
void Dessin(TaskBar* t)
{
	Fenetre* f3 = new Fenetre("draw",Point(23,1),"Draw",1,15,40,25,2,0,SupprimerDessin);
	new Bouton("save",f3,Point(7,0),11,1,2,"Sauvegarder",0,7,SauvegarderDessin);
	new Bouton("load",f3,Point(22,0),10,1,2,"Charger",0,7,ChargerDessin);
	new Bouton("noir",f3,Point(0,3),1,1,1," ",0,0,CouleurPinceau);
	new Bouton("blanc",f3,Point(0,6),1,1,1," ",15,15,CouleurPinceau);
	new Bouton("rouge",f3,Point(0,9),1,1,1," ",4,4,CouleurPinceau);
	new Bouton("bleu",f3,Point(0,12),1,1,1," ",1,1,CouleurPinceau);
	new Bouton("jaune",f3,Point(0,15),1,1,1," ",14,14,CouleurPinceau);
	new Bouton("vert",f3,Point(0,18),1,1,1," ",2,2,CouleurPinceau);
	new ZoneDessin("dessin",f3,Point(4,3),f3->GetWidth()-4,f3->GetHeight(),1);
	t->AjouterFenetre(f3);
}
void CouleurPinceau(Bouton* b)
{
	char* couleur = strdup(b->GetName().c_str());
	if( strcmp(couleur,"noir") == 0 )
	{
		((ZoneDessin*)(Event::GetTaskbar()->GetFenetreByName("draw")->GetComposantByName("dessin")))->SetCouleur(0);
	}
	else if( strcmp(couleur,"blanc") == 0 )
	{
		((ZoneDessin*)(Event::GetTaskbar()->GetFenetreByName("draw")->GetComposantByName("dessin")))->SetCouleur(15);
	}
	else if( strcmp(couleur,"rouge") == 0 )
	{
		((ZoneDessin*)(Event::GetTaskbar()->GetFenetreByName("draw")->GetComposantByName("dessin")))->SetCouleur(4);
	}
	else if( strcmp(couleur,"bleu") == 0 )
	{
		((ZoneDessin*)(Event::GetTaskbar()->GetFenetreByName("draw")->GetComposantByName("dessin")))->SetCouleur(1);
	}
	else if( strcmp(couleur,"jaune") == 0 )
	{
		((ZoneDessin*)(Event::GetTaskbar()->GetFenetreByName("draw")->GetComposantByName("dessin")))->SetCouleur(14);
	}
	else if( strcmp(couleur,"vert") == 0 )
	{
		((ZoneDessin*)(Event::GetTaskbar()->GetFenetreByName("draw")->GetComposantByName("dessin")))->SetCouleur(2);
	}
}
void SauvegarderDessin(Bouton* b)
{
	string result;
	Console::viderConsole();
	Console::gotoxy(0,0);
	Console::setColor(7,0);
	cout<<"PATH du fichier de sauvegarde?"<<endl;
	cin>>result;
	string command;
	command += "copy ";
	command += ((ZoneDessin*)(Event::GetTaskbar()->GetFenetreByName("draw")->GetComposantByName("dessin")))->GetFichier();
	command += " ";
	command += result;
	system(command.c_str());
	Event::Afficher();
}
void ChargerDessin(Bouton* b)
{
	string result;
	Console::viderConsole();
	Console::gotoxy(0,0);
	Console::setColor(7,0);
	cout<<"PATH du fichier a charger?"<<endl;
	cin>>result;
	string command;
	command += "copy ";
	command += result;
	command += " ";
	command += ((ZoneDessin*)(Event::GetTaskbar()->GetFenetreByName("draw")->GetComposantByName("dessin")))->GetFichier();
	system(command.c_str());
	Event::Afficher();
}
void SupprimerCalculatrice(Fenetre* f)
{
	Event::SupprimerFenetre(Event::GetTaskbar()->GetFenetreByName("calc"));
}
void SupprimerDessin(Fenetre* f)
{
	Event::SupprimerFenetre(Event::GetTaskbar()->GetFenetreByName("draw"));
}
void SupprimerTest(Fenetre* f)
{
	Event::SupprimerFenetre(Event::GetTaskbar()->GetFenetreByName("test"));
}

