#ifndef __MODULESCENE1_H__
#define __MODULESCENE1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleScene1 : public Module
{
public:
	ModuleScene1();
	~ModuleScene1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Texture* moto = nullptr;
	SDL_Texture* items = nullptr;
	SDL_Texture* win = nullptr;
	SDL_Texture* level = nullptr;
	SDL_Rect foreground;
	Animation ammo_grenades_colours;
	Animation ammo_specialgrenade1;
	Animation moto_go;
	Animation lvl1;
	Animation win1;
	Animation moto_stop;
	SDL_Rect background;
	SDL_Rect r;
	Animation* current_animation = nullptr;
	int cont5;
	int cont7;

	bool cont8 = false;
	bool cont6 = false;
	bool check = true;
	int w = 0, h = SCREEN_HEIGHT - 2880;
	int w_m = 255, h_m = 20;
	double long contador = 0;

	bool check_audio = true, check_audio1 = true, check_audio2 = true, check_audio3 = true;
	//Camera parameters
	int cont = 0, speed = 3;

	int tempo1 = 0;
	bool check_UI = true;
	bool winB = false;
};




#endif // __MODULESCENE1_H__