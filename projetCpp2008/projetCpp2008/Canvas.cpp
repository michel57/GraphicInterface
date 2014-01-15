#include "Canvas.h"
#include "Console.h"

Canvas::Canvas()
{
	this->parent = NULL;
	this->position = new Point();
	this->width = 0;
	this->height = 0;
	this->bordure = 0;
}
Canvas::Canvas(const Point& p,int width,int height,int styleBordure)
{
	this->parent = NULL;
	this->position = new Point(p);
	this->width = width;
	this->height = height;
	if( styleBordure == 0 || styleBordure == 1 || styleBordure == 2 )
	{
		this->bordure = styleBordure;
	}
	else
	{
		this->bordure = 1;
	}
}
Canvas::Canvas(const Canvas& c)
{
	this->parent = c.parent;
	this->position = new Point(*c.position);
	this->width = c.width;
	this->height = c.height;
	this->bordure = c.bordure;
}
Canvas::~Canvas()
{
	delete this->position;
}
Point* Canvas::GetPosition()const
{
	return this->position;
}
void Canvas::SetPosition(int x,int y)
{
	delete this->position;
	this->position = new Point(x,y);
}
void Canvas::SetPosition(const Point& p)
{
	delete this->position;
	this->position = new Point(p);
}
int Canvas::GetBordure()const
{
	return this->bordure;
}
void Canvas::SetBordure(int bordure)
{
	this->bordure = bordure;
}
int Canvas::GetWidth()const
{
	return this->width;
}
void Canvas::SetWidth(int width)
{
	this->width = width;
}
int Canvas::GetHeight()const
{
	return this->height;
}
void Canvas::SetHeight(int height)
{
	this->height = height;
}
Canvas* Canvas::GetParent()const
{
	return this->parent;
}
void Canvas::SetParent(Canvas* c)
{
	this->parent = c;
}
void Canvas::DessinerBordure()const
{
	Console::setColor(7,0);
	for(int i=this->position->GetX();i<this->position->GetX()+this->width;i++)
	{
		for(int j=this->position->GetY();j<this->position->GetY()+this->height;j++)
		{
			Console::gotoxy(i,j);
			if( i == this->position->GetX() && j == this->position->GetY() )
			{
				/*Affichage du caractère ascii situé représentant le coin en haut à gauche du rectangle.*/
				if(this->GetBordure() == 0)
					cout<<" ";
				else if(this->GetBordure() == 1)
					cout<<"\xDA";
				else if(this->GetBordure() == 2)
					cout<<"\xC9";
			}
			else if( i > this->position->GetX() && i < this->position->GetX()+this->width-1 && j == this->position->GetY() )
			{
				/*Ligne du haut entre les 2 coins haut gauche et haut droite  */
				if(this->GetBordure() == 0)
					cout<<" ";
				else if( this->GetBordure() == 1)
					cout<<"\xC4";
				else if(this->GetBordure() == 2)
					cout<<"\xCD";
			}
			else if( i == this->position->GetX()+this->width-1 && j == this->position->GetY() )
			{
				 //Affichage du caractère ascii situé représentant le coin en haut à droite du rectangle.
				if(this->GetBordure() == 0)
					cout<<" ";
				else if( this->GetBordure() == 1)
					cout<<"\xBF";
				else if(this->GetBordure() == 2)
					cout<<"\xBB";
			}
			else if( (i == this->position->GetX() || i == this->position->GetX()+this->width-1) && j < this->position->GetY()+this->height-1 )
			{
				//verticales
				if(this->GetBordure() == 0)
					cout<<" ";
				else if( this->GetBordure() == 1)
					cout<<"\xB3";
				else if(this->GetBordure() == 2)
					cout<<"\xBA";
			}
			else if( i == this->position->GetX() && j == this->position->GetY()+this->GetHeight()-1 )
			{
				//coin bas gauche
				if(this->GetBordure() == 0)
					cout<<" ";
				else if( this->GetBordure() == 1)
					cout<<("\xC0"); 
				else if(this->GetBordure() == 2)
					cout<<"\xC8";
			}
			else if( i > this->position->GetX() && i < this->position->GetX()+this->width-1 && j == this->position->GetY()+this->height-1 )
			{
				//ligne bas
				if(this->GetBordure() == 0)
					cout<<" ";
				else if( this->GetBordure() == 1)
					cout<<("\xC4");
				else if(this->GetBordure() == 2)
					cout<<"\xCD";
			}
			else if( i == this->position->GetX()+this->width-1 && j == this->position->GetY()+this->height-1 )
			{
				//coin bas droite
				if(this->GetBordure() == 0)
					cout<<" ";
				else if( this->GetBordure() == 1)
					cout<<("\xD9");
				else if(this->GetBordure() == 2)
					cout<<"\xBC";
			}
		}
	}
	Console::gotoxy(this->position->GetX(),this->position->GetY());
}

ostream& operator<<(ostream& s, const Canvas& c)
{
	c.DessinerBordure();
	return s;
}