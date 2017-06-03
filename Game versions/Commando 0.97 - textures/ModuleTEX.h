#ifndef __ModuleTEX_H__
#define __ModuleTEX_H__

#include "Module.h"
#include "Globals.h"

#define MAX_TEXTURES 50

class ModuleTEX : public Module
{
public:
	ModuleTEX();
	~ModuleTEX();

	SDL_Texture* A;
	SDL_Texture* B;
	SDL_Texture* C;
	SDL_Texture* D;

	SDL_Texture* E;
	SDL_Texture* F;
	SDL_Texture* G;
	SDL_Texture* H;

	SDL_Texture* I;
	SDL_Texture* J;
	SDL_Texture* K;
	SDL_Texture* L;

	SDL_Texture* graphics2;
	SDL_Texture* helicopter;
	SDL_Texture* playerhelicopter;

	SDL_Texture* Gameover;

	SDL_Texture* alphabet;
	SDL_Texture* animation;

	SDL_Texture* sprites;

	SDL_Texture* graphics;
	SDL_Texture* grenade;
	SDL_Texture* newmodetxt;

	SDL_Texture* JANE;

	SDL_Texture* Hud2;

	SDL_Texture* moto1;
	SDL_Texture* items1;
	SDL_Texture* graphics1;
	SDL_Texture* win1;
	SDL_Texture* end_door1;

	SDL_Texture* Hud;

	SDL_Texture* Inv;


	bool Init();
	bool CleanUp();

public:

};

#endif