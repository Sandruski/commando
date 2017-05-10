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

public:
	SDL_Texture* RoomE;
	SDL_Rect background;
	int w = 0, h = 0;


};







#endif // __ModuleSecretRoomE_H__
#pragma once
