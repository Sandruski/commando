#ifndef __MODULECINEMATICRADIO_H__
#define __MODULECINEMATICRADIO_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleCinematicRadio : public Module
{
public:
	ModuleCinematicRadio();
	~ModuleCinematicRadio();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* helicopter = nullptr;
	SDL_Texture* playerhelicopter = nullptr;
	SDL_Rect foreground;
	Animation playerenter;
	Animation helicopter1;
	Animation helicopter2;
	Animation helicopter3;
	Animation playerbye;
	Animation invisible;
	Animation playerleft;
	SDL_Rect background2;
	SDL_Rect r;
	Animation* current_animation = nullptr;


	bool check = true;
	float helialtura = 220;
	int w = 0, h = SCREEN_HEIGHT - 1728;
	double helicont = 0;
	int sj_y = 86, sj_x = 147;
	int pjcont = 0;
	bool contadorsalto;

	bool check_audio = true;
};




#endif // __MODULECINEMATIC_H__
