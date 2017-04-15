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
#include "ModuleParticles.h"

ModuleScene1::ModuleScene1()
{
	background.x = 0;
	background.y = 0;
	background.w = 256;
	background.h = 2880;

	ammo_grenades_colours.PushBack({ 179, 126, 33, 18 });
	ammo_grenades_colours.PushBack({ 179, 152, 33, 18 });
	ammo_grenades_colours.PushBack({ 179, 173, 33, 18 });
	ammo_grenades_colours.PushBack({ 179, 298, 33, 18 });
	ammo_grenades_colours.speed = 0.2f;

	ammo_specialgrenade1.PushBack({ 75, 227, 17, 16 });
	

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
	LOG("Loading 1st scene");

	moto = App->textures->Load("vehicles.png");
	items = App->textures->Load("items&HUD&snake.png");
	graphics = App->textures->Load("1-1.png");

	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	
	App->audio->pause_music();
	App->audio->play_music2();

	//Colliders
	App->collision->AddCollider({ 136,2817 - 2656,19,23 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 148,2800 - 2656,21,23 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 171,2817 - 2656,20,24 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 22,2769 - 2656,26,23 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 193,2705 - 2656,61,26 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 84,2640 - 2656,29,25 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,2642 - 2656,43,25 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 133,2594 - 2656,19,23 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 170,2594 - 2656,21,23 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 150,2577 - 2656,20,24 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 84,2528 - 2656, 24, 22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 201,2486 - 2656,56,54 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 5,2418 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 43,2418 - 2656,19,23 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 22,2402 - 2656,20,24 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 133,2385 - 2656,55,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 85,2339 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 149,2289 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,2262 - 2656,57,50 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 213,2226 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 201,1926 - 2656,53,56 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 204,1749 - 2656,53,56 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,1989 - 2656,121,51 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 256,1927 - 2656,58,48 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 71,1861 - 2656,81,51 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 256,1750 - 2656,57,50 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,1702 - 2656,57,53 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 70,1698 - 2656,22,20 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 108,1698 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 86,1682 - 2656,24,19 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 22,1538 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 149,1538 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 86,1472 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 195,1470 - 2656,57,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,1343 - 2656,100,81 }, COLLIDER_WALL, this);  //Pont
	App->collision->AddCollider({ 156,1343 - 2656,100,81 }, COLLIDER_WALL, this); //Pont
																				  //-------------- Pedres
	App->collision->AddCollider({ 0,1204 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 49,1140 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 161,1140 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 196,1087 - 2656,56,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 33,1060 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 113,1029 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 178,997 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,1007 - 2656,56,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 160,933 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 16,853 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 113,853 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 209,853 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 210,718 - 2656,45,81 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 6,737 - 2656,21,19 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 44,737 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 22,721 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 67,752 - 2656,56,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 147,671 - 2656,73,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 209,1456 - 2656,19,18 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,639 - 2656,56,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 100,575 - 2656,56,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,511 - 2656,75,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 212,389 - 2656,45,72 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,420 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 65,373 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 129,341 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 193,309 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 131,287 - 2656,56,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,116 - 2656,40,119 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 211,102 - 2656,47,119 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 35,79 - 2656,56,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 163,79 - 2656,56,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0, 0 - 2656,94,39 }, COLLIDER_WALL, this); //Muralla
	App->collision->AddCollider({ 161,0 - 2656,95,39 }, COLLIDER_WALL, this); //Muralla

																			  //AIGUA

	App->collision->AddCollider({ 0,2466 - 2656,57,40 }, COLLIDER_WATER, this);
	App->collision->AddCollider({ 40,1248 - 2656,47,27 }, COLLIDER_WATER, this);
	App->collision->AddCollider({ 168,1202 - 2656,94,75 }, COLLIDER_WATER, this);
	App->collision->AddCollider({ 0,241 - 2656,90,59 }, COLLIDER_WATER, this);

	return true;

}

// UnLoad assets
bool ModuleScene1::CleanUp()
{
	LOG("Unloading 1st scene");
	App->textures->Unload(graphics);

	App->collision->Disable();
	App->particles->Disable();
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleScene1::Update()
{
	update_status ret = UPDATE_CONTINUE;

	//Animation* current_animation = &moto_stop;

	App->render->Blit(graphics, w, h, &background);
	
	current_animation = &ammo_grenades_colours;
	r = current_animation->GetCurrentFrame();
	App->render->Blit(items, 153, 2464 - 2656, &r);
	App->render->Blit(items, 33, 1936 - 2656, &r);
	App->render->Blit(items, 30, 944 - 2656, &r);
	App->render->Blit(items, 44, 706 - 2656, &r);
	App->render->Blit(items, 1, 464 - 2656, &r);
	App->render->Blit(items, 155, 218 - 2656, &r);

	current_animation = &ammo_specialgrenade1;
	r = current_animation->GetCurrentFrame();
	App->render->Blit(items, 151, 2625 - 2656, &r);
	App->render->Blit(items, 185, 1149 - 2656, &r);


	//-2656
	if (App->player->position.y <= 1550 - 2656 && contador < 120) { /* && App->player->position.y >= 1300 - 2656 */
		if (w_m > 105) {
			current_animation = &moto_go;
			r = current_animation->GetCurrentFrame();
			App->render->Blit(moto, w_m, 1345 - 2656, &r);
			w_m--;
		}

		else if (w_m == 105) {
			current_animation = &moto_stop;
			r = current_animation->GetCurrentFrame();
			App->render->Blit(moto, w_m, 1345 - 2656, &r);
			contador++;
		}
	}

	else if (contador >= 120) {
		Animation* current_animation = &moto_go;
		r = current_animation->GetCurrentFrame();
		App->render->Blit(moto, w_m, 1345 - 2656, &r);
		w_m--;
	}
	
	
	
	// end

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 && KEY_DOWN) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->END, 3);
	}

	return ret;
}