#pragma once

#ifndef __MODULESECRETROOME_H__
#define __MODULESECRETROOME_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"


struct SDL_Texture;

class ModuleSecretRoomE : public Module
{
public:
	ModuleSecretRoomE();
	~ModuleSecretRoomE();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool check_audio = true;

	SDL_Rect background;
	int w = 0, h = 0;

	Animation PowerUp;

	uint lastTime, currentTime;


};







#endif // __ModuleSecretRoomE_H__
#pragma once
