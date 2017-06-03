#ifndef __MODULEENDINGLVL1_H__
#define __MODULEENDINGLVL1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"


struct SDL_Texture;

class ModuleEndingLvl1 : public Module
{
public:
	ModuleEndingLvl1();
	~ModuleEndingLvl1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* alphabet = nullptr;
	SDL_Texture* animation = nullptr;
	SDL_Rect a;
	SDL_Rect b;
	SDL_Rect c;
	SDL_Rect d;
	SDL_Rect e;
	SDL_Rect f;
	SDL_Rect g;
	SDL_Rect h;
	SDL_Rect i;
	SDL_Rect j;
	SDL_Rect k;
	SDL_Rect l;
	SDL_Rect m;
	SDL_Rect n;
	SDL_Rect o;
	SDL_Rect p;
	SDL_Rect q;
	SDL_Rect r;
	SDL_Rect s;
	SDL_Rect t;
	SDL_Rect u;
	SDL_Rect v;
	SDL_Rect w;
	SDL_Rect x;
	SDL_Rect y;
	SDL_Rect z;
	SDL_Rect redzero;
	SDL_Rect redone;
	SDL_Rect redtwo;
	SDL_Rect redthree;
	SDL_Rect redfour;
	SDL_Rect redfive;
	SDL_Rect redsix;
	SDL_Rect redseven;
	SDL_Rect redeight;
	SDL_Rect rednine;
	SDL_Rect highsc;
	SDL_Rect zero;
	SDL_Rect one;
	SDL_Rect two;
	SDL_Rect three;
	SDL_Rect four;
	SDL_Rect five;
	SDL_Rect six;
	SDL_Rect seven;
	SDL_Rect eight;
	SDL_Rect nine;
	SDL_Rect pone;
	Animation guy;

	int contador = 0;

	float time = 0;

};

#endif // __MODULEENDINGINGLVL1_H__
