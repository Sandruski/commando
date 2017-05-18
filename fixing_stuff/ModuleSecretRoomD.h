#ifndef __MODULESECRETROOMD_H__
#define __MODULESECRETROOMD_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"


struct SDL_Texture;

class ModuleSecretRoomD : public Module
{
public:
	ModuleSecretRoomD();
	~ModuleSecretRoomD();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* RoomD;
	SDL_Rect background;
	int w = 0, h = 0;

	int check_player = 0;
};




#endif // __ModuleSecretRoomB_H__