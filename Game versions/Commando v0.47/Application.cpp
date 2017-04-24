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
#include "ModuleParticlesGrenade.h"
#include "ModuleParticlesGrenade1.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "ModuleSaveData.h"

Application::Application()
{
	unsigned int index_module = 0;

	modules[index_module++] = window = new ModuleWindow();
	modules[index_module++] = render = new ModuleRender();
	modules[index_module++] = input = new ModuleInput();
	modules[index_module++] = textures = new ModuleTextures();
	modules[index_module++] = savedata = new ModuleSaveData();
	modules[index_module++] = fonts = new ModuleFonts();
	//modules[4] = scene_2 = new ModuleScene2();

	modules[index_module++] = Menu = new ModuleMenu();
	modules[index_module++] = cinematic = new ModuleCinematic();
	modules[index_module++] = scene_1 = new ModuleScene1();
	modules[index_module++] = END = new ModuleEND();


	modules[index_module++] = player = new ModulePlayer();
	modules[index_module++] = collision = new ModuleCollision();

	modules[index_module++] = particles = new ModuleParticles();
	modules[index_module++] = particlesenemies = new ModuleParticlesEnemies();
	modules[index_module++] = particlesgrenade = new ModuleParticlesGrenade();
	modules[index_module++] = particlesgrenade1 = new ModuleParticlesGrenade1();

	modules[index_module++] = enemies = new ModuleEnemies();

	modules[index_module++] = fade = new ModuleFadeToBlack();
	modules[index_module++] = audio = new ModuleAudio();

	modules[index_module] = UI = new ModuleUI();
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