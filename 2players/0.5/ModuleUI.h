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
	SDL_Texture* Inv = nullptr;
	Animation Inv1;
	SDL_Rect MarcadorVida, MarcadorVida2;
	SDL_Rect vida0;
	SDL_Rect vida1;
	SDL_Rect vida2;
	SDL_Rect vida3;
	SDL_Rect lvl1;
	SDL_Rect MarcadorGranada;
	SDL_Rect r;
	Animation* current_animation = nullptr;
	int font_score = -1;
	char score_text[10];
	uint score, score2;
	uint grenade = 3;
	uint cont = 0;
	char str1[10];
	char str2[10];
	char str3[10];
	char str4[10];
	char str5[10];
	int tempo1;

	bool check_sleep = true, check_UI = true;


	//bool characterselection_ui;
private:

	int var;
	int var2;
	bool gate;
};
#endif