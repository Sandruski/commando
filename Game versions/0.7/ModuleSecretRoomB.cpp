#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleMenu.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleEND.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleEnding.h"
#include "ModuleEnemies.h"
#include "ModuleScene1.h"
#include "ModuleCollision.h"
#include "ModuleParticlesEnemies.h"
#include "ModuleParticlesGrenade.h"
#include "ModuleParticlesGrenade1.h"
#include "ModuleParticles.h"
#include "ModuleCinematic.h"
#include "ModuleUI.h"
#include "ModuleSecretRoom1A.h"
#include "ModuleSecretRoomB.h"
#include "ModuleSecretRoomC.h"
#include "ModuleSecretRoomD.h"
#include "ModuleSecretRoomE.h"
#include <windows.h>

ModuleSecretRoomB::ModuleSecretRoomB(){

}
ModuleSecretRoomB::~ModuleSecretRoomB(){

}

bool ModuleSecretRoomB::Start(){
	RoomB = App->textures->Load("Assets/Background/Secret_Rooms/1-1/salasecretea1-B.png");
	background.x = 0;
	background.y = 0;
	background.w = 256;
	background.h = 224;

	App->collision->Enable();
	App->particles->Enable();
	App->particlesenemies->Enable();
	App->particlesgrenade->Enable();
	App->particlesgrenade1->Enable();
	App->player->Enable();
	App->enemies->Enable();
	App->UI->Enable();

	App->player->current_animation = &App->player->forward;
	App->player->stairsDown = true;
	App->player->move = true;

	//Camera and player parametres
	App->player->position.x = SCREEN_WIDTH / 2;
	App->player->position.y = 185;
	App->scene_1->current_start_pos = 0;
	App->render->camera.y = 0;
	App->scene_1->cont = 0;

	//COLLIDERS
	App->collision->AddCollider({ 15,30, 240, 15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 208,38, 48, 24 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 240,61, 16, 163 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,216, 242, 8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,38, 16, 186 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 15,72, 65, 50 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 208 ,60, 6, 26 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 217, 57, 15, 8 }, COLLIDER_SECRET_ROOM, this);

	//Grenades
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 100, 49);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 133, 49);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 121, 68);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 155, 68);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 114, 85);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 151, 85);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 124, 103);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 173, 103);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 94, 118);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 147, 118);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 138, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 164, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 100, 148);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 138, 148);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 125, 166);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 172, 166);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 92, 182);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 156, 182);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 135, 196);
	App->enemies->AddEnemy(ENEMY_TYPES::GRENADE, 172, 196);

	return true;
}
update_status ModuleSecretRoomB::Update(){
	App->render->Blit(RoomB, w, h, &background);

	if (App->input->keyboard[SDL_SCANCODE_1] == 1 && KEY_DOWN) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->room1A, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_2] == 1 && KEY_DOWN) {
		App->render->UP = false;

		App->scene_1->start = false;
		App->scene_1->start1 = false;
		App->scene_1->start2 = false;
		App->scene_1->start3 = true;
		App->scene_1->start4 = false;
		App->scene_1->start5 = false;

		App->fade->FadeToBlack(this, App->scene_1, 1);

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
		App->fade->FadeToBlack(this, App->roomE, 1);
	}

	return UPDATE_CONTINUE;
}
bool ModuleSecretRoomB::CleanUp(){
	App->textures->Unload(RoomB);

	App->UI->Disable();
	App->enemies->Disable();
	App->player->Disable();
	App->particlesgrenade1->Disable();
	App->particlesgrenade->Disable();
	App->particlesenemies->Disable();
	App->particles->Disable();
	App->collision->Disable();

	return true;
}
