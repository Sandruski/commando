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
	SDL_Texture* level = nullptr;
	SDL_Rect MarcadorVida;
	SDL_Rect vida0;
	SDL_Rect vida1;
	SDL_Rect vida2;
	SDL_Rect vida3;
	SDL_Rect lvl1;
	SDL_Rect MarcadorGranada;
	int font_score = -1;
	char score_text[10];
	uint score;
	uint grenade = 3;
	uint cont = 0;
	char str1[10];
	char str2[10];
	char str3[10];
	int tempo1;

	bool check_sleep = true, check_UI = true;


	//bool characterselection_ui;
private:

	int var;
	int var2;
	bool gate;
};
#endif