#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleScene1.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMenu.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleCinematic.h"
#include "ModuleUI.h"
#include "ModuleFonts.h"
#include "ModuleSaveData.h"

#include<stdio.h>
#include<string.h>


ModuleMenu::ModuleMenu()
{
	background.x = 10;
	background.y = 0;
	background.w = 256;
	background.h = 224;

	grenades.x = 54;
	grenades.y = 225;
	grenades.w = 20;
	grenades.h = 20;
}

ModuleMenu::~ModuleMenu()
{}

// Load assets
bool ModuleMenu::Start()
{

	App->UI->Disable();
	App->player->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->cinematic->Disable();
	LOG("Loading menu scene");

	graphics = App->textures->Load("menu.png");
	grenade = App->textures->Load("items&HUD&snake.png");
	App->audio->play_music1();

	//Initialize camera and others (prepare it for use)
	App->render->camera.x = App->render->camera.y = 0;
	App->scene_1->cont = 0;

	App->player->position.x = App->fade->start_x;
	App->player->position.y = App->fade->start_y;

	return true;
}

// UnLoad assets
bool ModuleMenu::CleanUp()
{

	App->UI->score = 0;
	//App->player->Enable();
	//App->player->destroyed = false;
	//find both things in ModuleCinematic

	LOG("Unloading menu scene");
	return true;
}

// Update: draw background
update_status ModuleMenu::Update()
{
	update_status ret = UPDATE_CONTINUE;


	if (!App->render->Blit(graphics, 0, SCREEN_HEIGHT - 224, &background, 0.75f))
		ret = UPDATE_ERROR;

	if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN) {

		App->audio->play_fx2();
		move_y += 16;

		if (move_y == 182) {
			move_y -= 16 * 4;
		}
	}

	App->render->Blit(grenade, 71, move_y, &grenades, 0.75f);


	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 && KEY_DOWN && move_y == 118) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->cinematic, 3);

	}

	sprintf_s(App->UI->str1, "%i", App->savedata->savescore_p1);
	App->fonts->BlitText(18, 27, App->savedata->font_score, App->UI->str1);

	sprintf_s(App->UI->str2, "%i", App->savedata->savescore);
	App->fonts->BlitText(104, 27, App->savedata->font_score2, App->UI->str2);


	return ret;
}