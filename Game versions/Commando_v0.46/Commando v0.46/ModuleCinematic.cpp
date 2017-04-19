#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleScene1.h"
#include "ModuleCinematic.h"
#include "ModuleMenu.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleEND.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "Module.h"

ModuleCinematic::ModuleCinematic()
{
	background2.x = 0;
	background2.y = 0;
	background2.w = 256;
	background2.h = 2880;

	playerjump.PushBack({ 98, 43, 18, 25 });

	playerbye.PushBack({ 131, 44, 20, 27 });
	playerbye.PushBack({ 149, 44, 20, 27 });
	playerbye.speed = 0.1f;

	playerleft.PushBack({ 5, 41, 19, 25 });
	playerleft.PushBack({ 23, 42, 19, 25 });
	playerleft.speed = 0.1f;

	helicopter1.PushBack({ 170, 49, 166, 127 });
	helicopter1.PushBack({ 168, 190, 166, 127 });
	helicopter1.PushBack({ 404, 90, 166, 127 });
	helicopter1.speed = 0.2f;

	helicopter3.PushBack({ 404, 289, 166, 127 });
	helicopter3.PushBack({ 405, 505, 166, 127 });
	helicopter3.PushBack({ 405, 782, 166, 127 });
	helicopter3.speed = 0.2f;

	helicopter2.PushBack({ 755, 160, 166, 161 });
	helicopter2.PushBack({ 752, 370, 166, 161 });
	helicopter2.PushBack({ 762, 798, 166, 161 });
	helicopter2.speed = 0.2f;
}

ModuleCinematic::~ModuleCinematic()
{}

// Load assets
bool ModuleCinematic::Start()
{
	App->collision->Disable();
	App->particles->Disable();
	App->player->Disable();

	LOG("Loading cinematic scene");
	helicopter = App->textures->Load("helicopterfix.png");
	graphics2 = App->textures->Load("1-1.png");
	playerhelicopter = App->textures->Load("spritesheet_humanos.png");

	return true;
}

// UnLoad assets
bool ModuleCinematic::CleanUp()
{
	LOG("Unloading 1st scene");
	App->textures->Unload(graphics2);
	App->player->Enable();
	App->player->destroyed = false;
	helicont = 0;

	return true;
}

// Update: draw background
update_status ModuleCinematic::Update()
{
	update_status ret = UPDATE_CONTINUE;

	//Animation* current_animation = &moto_stop;

	App->render->Blit(graphics2, w, h, &background2);


	/*
	current_animation = &playerbye;
	r = current_animation->GetCurrentFrame();
	App->render->Blit(playerhelicopter, 160 , 160, &r);
	*/


	if (helicont < 350) {
		current_animation = &helicopter1;
		r = current_animation->GetCurrentFrame();
		App->render->Blit(helicopter, 128 - 80, helialtura, &r);
		helicont++;
		if (helialtura > 10)
			helialtura--;
	}
	else if (helicont >= 350 && helicont < 370) {
		current_animation = &helicopter2;
		r = current_animation->GetCurrentFrame();
		App->render->Blit(helicopter, 128 - 80, helialtura - 20, &r);
		helicont++;
	}
	else if (helicont >= 370 && helicont < 410) {
		//helicopter alt i adeu
		current_animation = &helicopter3;
		r = current_animation->GetCurrentFrame();
		App->render->Blit(helicopter, 128 - 80, helialtura - 10, &r);
		helicont++;
	}
	else if (helicont >= 410 && helicont < 430) {
		//helicopter alt i adeu
		current_animation = &helicopter2;
		r = current_animation->GetCurrentFrame();
		App->render->Blit(helicopter, 128 - 80, helialtura - 20, &r);
		helicont++;
	}
	else if (helicont >= 430 && helicont <= 1000) {
		//helicopter alt i adeu
		current_animation = &helicopter1;
		r = current_animation->GetCurrentFrame();
		App->render->Blit(helicopter, 128 - 80, helialtura, &r);
		helicont++;
		helialtura--;
	}


	if (helicont >= 370 && helicont < 480) {
		if (pjcont == 0 || pjcont == 1)
			current_animation = &playerjump;
		else if (pjcont == 2)
			current_animation = &playerbye;
		r = current_animation->GetCurrentFrame();
		App->render->Blit(playerhelicopter, sj_x, sj_y + 5, &r);
		if (helicont >= 370 < 565) {
			if (pjcont == 0) {
				//if (contadorsalto == true) {
				sj_y--;
				sj_x++;
				if (sj_y < 60)
					pjcont = 1;
				//	contadorsalto = false;
				//}
			}
			if (pjcont == 1) {
				sj_y++;
				sj_x++;
				if (sj_y >= 101)
					pjcont = 2;
			}
		}
	}
	if (helicont >= 480) {
		current_animation = &playerleft;
		r = current_animation->GetCurrentFrame();
		App->render->Blit(playerhelicopter, sj_x, sj_y + 5, &r);
		if (sj_x > 125)
			sj_x--;

	}


	if (sj_x == 125) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->scene_1, 1);
	}

	return ret;
}