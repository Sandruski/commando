#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleScene1.h"
#include "ModuleMenu.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleScene2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"

ModuleScene1::ModuleScene1()
{
	background.x = 0;
	background.y = 0;
	background.w = 256;
	background.h = 2880;

	moto_go.PushBack({ 20, 22, 47, 23 });
	moto_go.speed = 0.2f;

	moto_stop.PushBack({ 73, 17, 47, 29 });
	moto_stop.PushBack({ 130, 19, 47, 26 });
	moto_stop.PushBack({ 187, 17, 47, 28 });
	moto_stop.speed = 0.1f;
}

ModuleScene1::~ModuleScene1()
{}

// Load assets
bool ModuleScene1::Start()
{
	App->player->Enable();
	LOG("Loading 1st scene");
	graphics = App->textures->Load("1-1.png");
	moto = App->textures->Load("vehicles.png");
	App->audio->pause_music();
	App->audio->play_music2();
	return true;
}

// UnLoad assets
bool ModuleScene1::CleanUp()
{
	App->player->Disable();
	LOG("Unloading 1st scene");
	return true;
}

// Update: draw background
update_status ModuleScene1::Update()
{
	update_status ret = UPDATE_CONTINUE;

	//Animation* current_animation = &moto_go;
	Animation* current_animation = &moto_stop;

	if (!App->render->Blit(graphics, w, h, &background, 0.75f))
		ret = UPDATE_ERROR;
	
	SDL_Rect r = current_animation->GetCurrentFrame();

	if (h >= SCREEN_HEIGHT - 1550) {
		App->render->Blit(moto, w_m, h_m, &r, 0.75f);
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 && KEY_DOWN) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->scene_2, 3);
	}

	return ret;
}