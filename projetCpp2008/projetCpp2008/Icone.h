#ifndef __Icone__
#define __Icone__

#include "Canvas.h"
#include "Image.h"
#include "Label.h"

class Icone:public Canvas{

private:
	Image* img;  //img(4*2)
	Label* lbl;  //lbl(8)
	void (*clickFunction)(Icone*);
public:
	Icone();
	Icone(Point position,const char* lienImageIcone,const char* lbl,int bordure=0,void(*clickAction)(Icone*)=NULL);
	Icone(const Icone&);
	virtual ~Icone();
	Image* GetImg()const;
	void SetImg(Image*);
	Label* GetLbl()const;
	void SetLbl(Label*);
	int GetImgWidth()const { return 4; };
	int GetImgHeight()const { return 2; };
	void actionClick();
	friend ostream& operator<<(ostream&,const Icone&);
};
#endif;