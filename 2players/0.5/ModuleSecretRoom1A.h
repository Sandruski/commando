#ifndef __MODULESECRETROOM1A_H__
#define __MODULESECRETROOM1A_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"


struct SDL_Texture;

class ModuleSecretRoom1A : public Module
{
public:
	ModuleSecretRoom1A();
	~ModuleSecretRoom1A();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* Room1A;
	SDL_Rect background;
	int w = 0, h = 0;


};







#endif // __ModuleSecretRoom1A_H__
#pragma once