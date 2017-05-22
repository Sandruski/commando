#ifndef __ModuleSaveData_H__
#define __ModuleSaveData_H__

#include "Module.h"
#include "SDL\include\SDL_rect.h"
#include <fstream>

using namespace std;

class ModuleSaveData : public Module
{
public:
	ModuleSaveData();
	~ModuleSaveData();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	int savescore;
	fstream scorefile;
	int savescore2p;
	int savescore_p1;
	int font_score;
	int font_score2;
	SDL_Texture* Hud2 = nullptr;
};

#endif //__ModuleSaveData_H__