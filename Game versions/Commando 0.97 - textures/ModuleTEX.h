#ifndef __ModuleTEX_H__
#define __ModuleTEX_H__

#include "Module.h"
#include "Globals.h"

class ModuleTEX : public Module
{
public:
	ModuleTEX();
	~ModuleTEX();

	SDL_Texture* A = nullptr;
	SDL_Texture* B = nullptr;
	SDL_Texture* C = nullptr;
	SDL_Texture* D = nullptr;

	SDL_Texture* E = nullptr;
	SDL_Texture* F = nullptr;
	SDL_Texture* G = nullptr;
	SDL_Texture* H = nullptr;

	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* helicopter = nullptr;
	SDL_Texture* playerhelicopter = nullptr;

	SDL_Texture* Gameover = nullptr;

	SDL_Texture* alphabet = nullptr;
	SDL_Texture* animation = nullptr;

	SDL_Texture* sprites = nullptr;

	SDL_Texture* graphics = nullptr;
	SDL_Texture* grenade = nullptr;
	SDL_Texture* newmodetxt = nullptr;

	SDL_Texture* JANE = nullptr;

	SDL_Texture* Hud2 = nullptr;

	SDL_Texture* moto1 = nullptr;
	SDL_Texture* items1 = nullptr;
	SDL_Texture* graphics1 = nullptr;
	SDL_Texture* win1 = nullptr;
	SDL_Texture* end_door1 = nullptr;

	SDL_Texture* Hud = nullptr;

	SDL_Texture* Inv = nullptr;

	bool Init();
	bool CleanUp();

public:

};

#endif