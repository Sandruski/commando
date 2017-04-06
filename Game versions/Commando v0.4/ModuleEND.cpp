#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleScene1.h"
#include "ModulePlayer.h"
#include "ModuleMenu.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEND.h"
#include "ModuleCollision.h"

ModuleEND::ModuleEND()
{
	background.x = 70;
	background.y = 50;
	background.w = 280;
	background.h = 250;
}

ModuleEND::~ModuleEND()
{}

// Load assets
bool ModuleEND::Start()
{
	App->player->Enable();
	App->collision->Disable();
	LOG("Loading end scene");
	graphics = App->textures->Load("highscore.png");
	App->audio->pause_music();
	return true;
}

// UnLoad assets
bool ModuleEND::CleanUp()
{
	App->player->Disable();
	LOG("Unloading END scene");
	return true;
}

// Update: draw background
update_status ModuleEND::Update()
{
	update_status ret = UPDATE_CONTINUE;

	if (!App->render->Blit(graphics, 0, SCREEN_HEIGHT - 224, &background, 0.75f))
		ret = UPDATE_ERROR;

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 && KEY_DOWN) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->Menu, 3);
		
	}

	return ret;
}
