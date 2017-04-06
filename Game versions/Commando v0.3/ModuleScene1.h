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
	SDL_Rect foreground;
	Animation moto_go;
	Animation moto_stop;
	SDL_Rect background;
	SDL_Rect r;
	Animation* current_animation = nullptr;

	bool check = true;
	int w = 0, h = SCREEN_HEIGHT - 2880;
	int w_m = 255, h_m = 20;

	//w_m = 255;
};




#endif // __MODULESCENE1_H__