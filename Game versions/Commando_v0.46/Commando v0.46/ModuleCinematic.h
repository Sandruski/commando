#ifndef __MODULECINEMATIC_H__
#define __MODULECINEMATIC_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleCinematic : public Module
{
public:
	ModuleCinematic();
	~ModuleCinematic();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* helicopter = nullptr;
	SDL_Texture* playerhelicopter = nullptr;
	SDL_Rect foreground;
	Animation helicopter1;
	Animation helicopter2;
	Animation helicopter3;
	Animation playerbye;
	Animation playerjump;
	Animation playerleft;
	SDL_Rect background2;
	SDL_Rect r;
	Animation* current_animation = nullptr;


	bool check = true;
	int helialtura = 220;
	int w = 0, h = SCREEN_HEIGHT - 2880;
	double helicont = 0;
	int sj_y = 86, sj_x = 147;
	int pjcont = 0;
	bool contadorsalto;
};




#endif // __MODULECINEMATIC_H__