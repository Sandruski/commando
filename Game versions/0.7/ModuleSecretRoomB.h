#ifndef __MODULESECRETROOMB_H__
#define __MODULESECRETROOMB_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"


struct SDL_Texture;

class ModuleSecretRoomB: public Module
{
public:
	ModuleSecretRoomB();
	~ModuleSecretRoomB();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool check_audio = true;

	SDL_Texture* RoomB;
	SDL_Rect background;
	int w = 0, h = 0;
};




#endif // __ModuleSecretRoomB_H__
