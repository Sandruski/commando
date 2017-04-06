#ifndef __MODULEMENU_H__
#define __MODULEMENU_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleMenu : public Module
{
public:
	ModuleMenu();
	~ModuleMenu();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* grenade = nullptr;
	SDL_Rect foreground;
	SDL_Rect background;
	SDL_Rect grenades;

	int move_y = 116;
};
#endif