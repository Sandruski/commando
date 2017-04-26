#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleScene1.h"
#include "ModuleMenu.h"
#include "ModuleEnding.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"
#include "ModuleEND.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleParticlesEnemies.h"
#include "ModuleParticlesGrenade.h"
#include "ModuleParticlesGrenade1.h"
#include "ModuleParticles.h"
#include "ModuleCinematic.h"
#include "ModuleUI.h"
#include <windows.h>

ModuleEnding::ModuleEnding()
{
	background2.x = 0;
	background2.y = 0;
	background2.w = 256;
	background2.h = 2880;
}

ModuleEnding::~ModuleEnding()
{}

// Load assets
bool ModuleEnding::Start()
{
	App->UI->Disable();
	App->enemies->Disable();
	App->collision->Disable();
	App->particlesgrenade1->Disable();
	App->particlesgrenade->Disable();
	App->particlesenemies->Disable();
	App->particles->Disable();
	App->player->Disable();

	LOG("Loading ending scene");
	black = App->textures->Load("black.png");

	//Initialize audio
	check_audio = true;
	check_audio1 = true;

	return true;
}

// UnLoad assets
bool ModuleEnding::CleanUp()
{
	LOG("Unloading ending scene");
	App->textures->Unload(black);

	App->player->play_ending = false;
	App->scene_1->play_win = false;

	return true;
}

// Update: draw background
update_status ModuleEnding::Update()
{
	update_status ret = UPDATE_CONTINUE;

	App->render->Blit(black, 0, SCREEN_HEIGHT - 2880, &background2);

	if (App->fade->on == this && yeah == true) {
		cont = 0;
		yeah = false;
	}

	cont++;

	//win
	if (check_audio && App->scene_1->play_win == true) {
		App->audio->play_music4();
		check_audio = false;
	}

	//lose
	if (check_audio1 && App->player->play_ending == true) {
		App->audio->play_music5();
		check_audio1 = false;
	}

	if (cont == 205) {
		App->fade->FadeToBlack(this, App->Menu, 1);
		yeah = true;
	}

	return ret;
}