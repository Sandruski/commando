#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleScene1.h"
#include "ModuleMenu.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleEND.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"

ModuleScene1::ModuleScene1()
{
	background.x = 0;
	background.y = 0;
	background.w = 256;
	background.h = 2880;

	/*moto_go.PushBack({ 20, 22, 47, 23 });
	moto_go.speed = 0.2f;

	moto_stop.PushBack({ 73, 17, 47, 29 });
	moto_stop.PushBack({ 130, 19, 47, 26 });
	moto_stop.PushBack({ 187, 17, 47, 28 });
	moto_stop.speed = 0.1f;*/
}

ModuleScene1::~ModuleScene1()
{}

// Load assets
bool ModuleScene1::Start()
{
	App->player->Enable();
	App->collision->Enable();
	LOG("Loading 1st scene");
	graphics = App->textures->Load("1-1.png");
	moto = App->textures->Load("vehicles.png");
	App->audio->pause_music();
	App->audio->play_music2();

	App->collision->AddCollider({ 131,(2817 - 2656),29,23 }, COLLIDER_WALL,this);
	App->collision->AddCollider({ 148,2800 - 2656,28,20 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 166,2817 - 2656,26,24 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 22,2769 - 2656,26,23 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 193,2705 - 2656,61,26 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 84,2640 - 2656,29,25 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,2642 - 2656,43,25 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 133,2594 - 2656,26,23 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 165,2594 - 2656,27,23 }, COLLIDER_WALL, this);
	/*App->collision->AddCollider({ 150,2577 - 2656,24,20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 84,2528 - 2656, 24, 22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5,2418 - 2656,24,22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 38,2418 - 2656,24,22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 22,2402 - 2656,24,22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 133,2385 - 2656,55,8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 85,2339 - 2656,24,22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 149,2289 - 2656,24,22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0,2262 - 2656,57,50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 213,2226 - 2656,24,22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0,1989 - 2656,121,51 }, COLLIDER_WALL);
	App->collision->AddCollider({ 256,1927 - 2656,58,48 }, COLLIDER_WALL);
	App->collision->AddCollider({ 71,1861 - 2656,81,51 }, COLLIDER_WALL);
	App->collision->AddCollider({ 256,1750 - 2656,57,50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0,1702 - 2656,57,79 }, COLLIDER_WALL);
	App->collision->AddCollider({ 70,1698 - 2656,24,22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 102,1698 - 2656,24,22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 86,1682 - 2656,24,22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 22,1538 - 2656,24,22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 149,1538 - 2656,24,22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 86,1472 - 2656,24,22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 195,1470 - 2656,57,8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0,1343 - 2656,100,81 }, COLLIDER_WALL);  //Pont
	App->collision->AddCollider({ 156,1343 - 2656,100,81 }, COLLIDER_WALL); //Pont
																	 //-------------- Pedres
	App->collision->AddCollider({ 0,1204 - 2656,32,15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 49,1140 - 2656,32,15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 161,1140 - 2656,32,15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 196,1087 - 2656,56,8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 33,1060 - 2656,32,15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 113,1029 - 2656,32,15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 178,997 - 2656,32,15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0,1007 - 2656,56,8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 160,933 - 2656,32,15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 16,853 - 2656,32,15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 113,853 - 2656,32,15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 209,853 - 2656,32,15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 256,718 - 2656,45,81 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6,737 - 2656,24,22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 38,737 - 2656,24,22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 22,721 - 2656,24,22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 67,752 - 2656,56,8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 147,671 - 2656,73,8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0,639 - 2656,56,8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 100,575 - 2656,56,8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0,511 - 2656,75,8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 256,389 - 2656,45,72 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0,420 - 2656,32,15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 65,373 - 2656,32,15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 129,341 - 2656,32,15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 193,309 - 2656,32,15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 131,287 - 2656,56,8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0,116 - 2656,40,119 }, COLLIDER_WALL);
	App->collision->AddCollider({ 256,102 - 2656,47,119 }, COLLIDER_WALL);
	App->collision->AddCollider({ 35,79 - 2656,56,8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 163,79 - 2656,56,8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0,0 - 2656,94,39 }, COLLIDER_WALL);//Muralla
	App->collision->AddCollider({ 256,0 - 2656,95,39 }, COLLIDER_WALL);//Muralla

																//AIGUA

	App->collision->AddCollider({ 0,2466 - 2656,63,48 }, COLLIDER_WATER);
	App->collision->AddCollider({ 32,1248 - 2656,33,33 }, COLLIDER_WATER);
	App->collision->AddCollider({ 256,1200 - 2656,94,81 }, COLLIDER_WATER);
	App->collision->AddCollider({ 0,241 - 2656,95,64 }, COLLIDER_WATER);*/

	return true;

}

// UnLoad assets
bool ModuleScene1::CleanUp()
{
	App->textures->Unload(graphics);
	App->player->Disable();
	App->collision->Disable();
	LOG("Unloading 1st scene");
	return true;
}

// Update: draw background
update_status ModuleScene1::Update()
{
	update_status ret = UPDATE_CONTINUE;

	//Animation* current_animation = &moto_stop;

	if (!App->render->Blit(graphics, w, h, &background, 0.75f))
		ret = UPDATE_ERROR;
	

	/*if (h >= SCREEN_HEIGHT - 1550 && h <= SCREEN_HEIGHT - 1450) {
		if (w_m > 105) {
			current_animation = &moto_go;
			r = current_animation->GetCurrentFrame();
			App->render->Blit(moto, w_m, h_m, &r, 0.75f);
			w_m--;
		}
		if (w_m == 105) {
			current_animation = &moto_stop;
			r = current_animation->GetCurrentFrame();
			App->render->Blit(moto, w_m, h_m, &r, 0.75f);
		}
	}
		else if (h > SCREEN_HEIGHT - 1450 && h < SCREEN_HEIGHT - 1200) {
			Animation* current_animation = &moto_go;
			r = current_animation->GetCurrentFrame();
			App->render->Blit(moto, w_m, h_m, &r, 0.75f);
			w_m--;			
	}	
	*/

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 && KEY_DOWN) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->END, 3);
	}

	return ret;
}