#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleScene1.h"
#include "ModuleScene2.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleEND.h"
#include "ModuleMenu.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleParticlesEnemies.h"
#include "ModuleEnemies.h"
#include "ModuleCinematic.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	//modules[4] = scene_2 = new ModuleScene2();

	modules[4] = Menu = new ModuleMenu();
	modules[5] = cinematic = new ModuleCinematic();
	modules[6] = scene_1 = new ModuleScene1();
	modules[7] = END = new ModuleEND();

	modules[8] = enemies = new ModuleEnemies();
	modules[9] = player = new ModulePlayer();


	modules[10] = particles = new ModuleParticles();
	modules[11] = particlesenemies = new ModuleParticlesEnemies();

	modules[12] = collision = new ModuleCollision();

	modules[13] = fade = new ModuleFadeToBlack();
	modules[14] = audio = new ModuleAudio();
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Player will be enabled on the first update of a new scene
	player->Disable();
	// Disable the map that you do not start with
	END->Disable();
	scene_1->Disable();
	collision->Disable();
//	scene_2->Disable();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}