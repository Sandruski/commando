#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSecretRoomB.h"
#include "ModuleMenu.h"
#include "ModulePlayer.h"
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
#include "ModuleSecretRoom1A.h"
#include "ModuleSecretRoomB.h"
#include "ModuleSecretRoomC.h"
#include "ModuleSecretRoomD.h"
#include "ModuleSecretRoomE.h"
#include "ModuleScene1.h"

ModuleSecretRoom1A::ModuleSecretRoom1A() {

}
ModuleSecretRoom1A::~ModuleSecretRoom1A() {

}

bool ModuleSecretRoom1A::Start() {
	Room1A = App->textures->Load("Assets/Background/Secret_Rooms/1-1/Commando 1-A.png");
	background.x = 0;
	background.y = 0;
	background.w = 256;
	background.h = 224;

	App->player->current_animation = &App->player->forward;
	App->player->move = true;
	App->collision->Enable();
	App->player->Enable();
	App->UI->Enable();
	App->enemies->Enable();

	//Camera and player parametres
	App->player->position.x = 130;
	App->player->position.y = 110;
	App->scene_1->current_start_pos = 0;
	App->render->camera.y = 0;
	App->scene_1->cont = 0;

	//COLLIDERS
	App->collision->AddCollider({ 0,0, 32, 153 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,151, 16, 71 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,216, 255, 8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 224,0, 32, 142 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 240,141, 16, 74 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 32,0, 132, 34 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 162,0, 29, 23 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 189,0, 35, 35 }, COLLIDER_WALL, this);

	//ENEMIES
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 167, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 53, 110);


	return true;
}
update_status ModuleSecretRoom1A::Update() {

	App->render->Blit(Room1A, w, h, &background);


	if (App->input->keyboard[SDL_SCANCODE_1] == 1 && KEY_DOWN) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->scene_1, 1);

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
		App->fade->FadeToBlack(this, App->roomE, 1);
	}
	return UPDATE_CONTINUE;
}
bool ModuleSecretRoom1A::CleanUp() {
	App->textures->Unload(Room1A);

	App->enemies->Disable();
	App->UI->Disable();
	App->player->Disable();
	App->collision->Disable();

	return true;
}