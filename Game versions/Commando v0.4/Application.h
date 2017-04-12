#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 12

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleScene1;
//class ModuleScene2;
class ModulePlayer;
class ModuleFadeToBlack;
class ModuleMenu;
class ModuleEND;
class ModuleParticles;
class ModuleCollision;
class ModuleAudio;
class Module;


class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleScene1* scene_1;
	//ModuleScene2* scene_2;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleMenu* Menu;
	ModuleParticles* particles;
	ModuleCollision* collision;
	ModuleEND* END;
	ModuleAudio* audio;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__