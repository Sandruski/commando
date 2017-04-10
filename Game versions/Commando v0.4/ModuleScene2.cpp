#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleMenu.h"
#include "SDL/include/SDL.h"
#include "ModuleScene2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEND.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"

ModuleScene2::ModuleScene2()
{
	background.x = 0;
	background.y = 0;
	background.w = 256;
	background.h = 2880;
}

ModuleScene2::~ModuleScene2()
{}

// Load assets
bool ModuleScene2::Start()
{
	App->player->Enable();
	//App->collision->Enable();
	LOG("Loading 2nd scene");
	graphics = App->textures->Load("1-2.png");
	App->audio->pause_music();
	App->audio->play_music3();

	return true;
}

// UnLoad assets
bool ModuleScene2::CleanUp()
{
	App->player->Disable();
	//App->collision->Disable();
	LOG("Unloading 2nd scene");
	return true;
}

// Update: draw background
update_status ModuleScene2::Update()
{
	update_status ret = UPDATE_CONTINUE;

	if (!App->render->Blit(graphics, w, h, &background, 0.75f))
		ret = UPDATE_ERROR;

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 && KEY_DOWN) {

		App->render->UP = false;
		App->fade->FadeToBlack(this, App->END, 3);
	}

	return ret;
}
