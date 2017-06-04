#ifndef __MODULEENDING_H__
#define __MODULEENDING_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleEnding : public Module
{
public:
	ModuleEnding();
	~ModuleEnding();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Rect foreground;
	SDL_Rect background2;
	SDL_Rect r;
	Animation* current_animation = nullptr;


	int cont;
	bool yeah;

	bool check_audio = true, check_audio1 = true;
};




#endif