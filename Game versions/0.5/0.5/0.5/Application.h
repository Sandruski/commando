#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 21

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleScene1;
class ModuleEnding;
//class ModuleScene2;
class ModulePlayer;
class ModuleFadeToBlack;
class ModuleMenu;
class ModuleParticles;
class ModuleCollision;
class ModuleAudio;
class ModuleCinematic;
class ModuleEnemies;
class ModuleParticlesEnemies;
class Module;
class ModuleFonts;
class ModuleUI;
class ModuleParticlesGrenade;
class ModuleParticlesGrenade1;
class ModuleSaveData;
class ModuleSecretRoomB;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleEnding* ending;
	ModuleTextures* textures;
	ModuleScene1* scene_1;
	//ModuleScene2* scene_2;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleMenu* Menu;
	ModuleParticles* particles;
	ModuleCollision* collision;
	ModuleCinematic* cinematic;
	ModuleAudio* audio;
	ModuleEnemies* enemies;
	ModuleParticlesEnemies* particlesenemies;
	ModuleUI* UI;
	ModuleFonts* fonts;
	ModuleParticlesGrenade* particlesgrenade;
	ModuleParticlesGrenade1* particlesgrenade1;
	ModuleSaveData* savedata;
	ModuleSecretRoomB * roomB;

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