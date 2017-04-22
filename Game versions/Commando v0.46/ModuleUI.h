#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleUI : public Module
{

public:
	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

	//void vidaPlayer(uint player);


public:

	SDL_Texture* Hud = nullptr;
	SDL_Texture* Hud2 = nullptr;

	SDL_Rect MarcadorVida;
	SDL_Rect vida0;
	SDL_Rect vida1;
	SDL_Rect vida2;
	SDL_Rect vida3;
	SDL_Rect MarcadorGranada;
	int font_score = -1;
	char score_text[10];
	uint score;
	uint grenade = 0;
	uint cont = 0;
	//bool characterselection_ui;
private:

	int var;
	int var2;
	bool gate;
};
#endif