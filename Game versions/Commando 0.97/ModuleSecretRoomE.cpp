#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSecretRoom1A.h"
#include "ModuleSecretRoomB.h"
#include "ModuleSecretRoomC.h"
#include "ModuleSecretRoomD.h"
#include "ModuleSecretRoomE.h"
#include "ModuleMenu.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleEND.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleEnding.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleParticlesEnemies.h"
#include "ModuleParticlesGrenade.h"
#include "ModuleParticlesGrenade1.h"
#include "ModuleParticles.h"
#include "ModuleCinematic.h"
#include "ModuleUI.h"
#include <windows.h>
#include "ModuleScene1.h"

ModuleSecretRoomE::ModuleSecretRoomE() {
	background.x = 0;
	background.y = 0;
	background.w = 256;
	background.h = 224;
}
ModuleSecretRoomE::~ModuleSecretRoomE() {

}

bool ModuleSecretRoomE::Start() {
	RoomE = App->textures->Load("Assets/Background/Secret_Rooms/1-1/1-E.png");
	GunUp = App->textures->Load("Assets/Sprites/Gun_PowerUp.png");
	

	check_audio = true;

	PowerUp.Reset();
	PowerUp.PushBack({ 15, 8, 128, 32 });
	PowerUp.PushBack({ 15, 51, 128, 32 });
	PowerUp.PushBack({ 1, 1, 1, 1 });
	PowerUp.speed = 0.01f;

	App->collision->Enable();
	App->particles->Enable();
	App->particlesenemies->Enable();
	App->particlesgrenade->Enable();
	App->particlesgrenade1->Enable();
	App->player->Enable();
	if (App->player2->twoplayerson == true)
	App->player2->Enable();
	App->enemies->Enable();
	App->UI->Enable();

	App->player->current_animation = &App->player->forward;
	App->player->stairsDown = true;
	App->player->move = true;
	App->player->SoldierPowerUp = 1;

	//Camera and player parametres
	App->player->position.x = SCREEN_WIDTH / 2;
	App->player->position.y = 185;
	App->player2->position.y = 160;
	App->scene_1->current_start_pos = 0;
	App->render->camera.y = 0;
	App->scene_1->cont = 0;
	
	//COLLIDERS
	App->collision->AddCollider({ 0,31, 116, 17 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 141,31, 115, 16 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 239,47, 16, 177 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 192,71, 49, 50 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 96,87, 63, 53 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,38, 16, 186 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,216, 256, 8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 121, 27, 15, 8 }, COLLIDER_SECRET_ROOM, this);

	//ENEMIES
	App->enemies->AddEnemy(ENEMY_TYPES::PRISONER, 131, 137);

	return true;
}
update_status ModuleSecretRoomE::Update() {
	App->render->Blit(RoomE, w, h, &background);

	if (check_audio) {
		App->audio->play_music10();
		check_audio = false;
	}


	if (App->player->SoldierPowerUp == 1)
		lastTime = SDL_GetTicks();
	else if (App->player->SoldierPowerUp == 2 && App->player->stairsUp == true) {
		App->player->move = false;
		App->player2->move = false;
		App->scene_1->current_animation = &PowerUp;
		App->scene_1->r = App->scene_1->current_animation->GetCurrentFrame();
		App->render->Blit(GunUp, 65, 55, &App->scene_1->r);
	}

	currentTime = SDL_GetTicks();
	currentTime -= lastTime;

	if (currentTime > 3500 && App->player->stairsUp == true) {
		App->player->move = true;
		App->player2->move = true;
		PowerUp.speed = 0;
		App->player->SoldierPowerUp = 1;
		App->player2->SoldierPowerUp = 1;
	}





	if (App->input->keyboard[SDL_SCANCODE_1] == 1 && KEY_DOWN) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->room1A, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_2] == 1 && KEY_DOWN) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->roomB, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_3] == 1 && KEY_DOWN) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->roomC, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_4] == 1 && KEY_DOWN) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->roomD, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_5] == 1 && KEY_DOWN) {
		App->render->UP = false;

		App->scene_1->start = false;
		App->scene_1->start1 = false;
		App->scene_1->start2 = false;
		App->scene_1->start3 = false;
		App->scene_1->start4 = false;
		App->scene_1->start5 = true;

		App->fade->FadeToBlack(this, App->scene_1, 1);
	}


	return UPDATE_CONTINUE;
}
bool ModuleSecretRoomE::CleanUp() {
	App->textures->Unload(RoomE);
	App->textures->Unload(GunUp);

	App->UI->Disable();
	App->enemies->Disable();
	App->player->Disable();
	if (App->player2->twoplayerson == true)
	App->player2->Disable();
	App->particlesgrenade1->Disable();
	App->particlesgrenade->Disable();
	App->particlesenemies->Disable();
	App->particles->Disable();
	App->collision->Disable();
	App->player->SoldierPowerUp = 0;

	return true;
}