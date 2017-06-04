#ifndef __MODULESECRETROOMC_H__
#define __MODULESECRETROOMC_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"


struct SDL_Texture;

class ModuleSecretRoomC : public Module
{
public:
	ModuleSecretRoomC();
	~ModuleSecretRoomC();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool check_audio = true;
	bool loop = false;

	SDL_Rect background;
	int w = 0, h = 0;

	int check_player = 0;
};




#endif // __ModuleSecretRoomB_H__