#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSecretRoomB.h"
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
#include "ModuleSecretRoom1A.h"
#include "ModuleSecretRoomB.h"
#include "ModuleSecretRoomC.h"
#include "ModuleSecretRoomD.h"
#include "ModuleSecretRoomE.h"
#include "ModuleScene1.h"

ModuleSecretRoom1A::ModuleSecretRoom1A() {
	background.x = 0;
	background.y = 0;
	background.w = 256;
	background.h = 224;
}
ModuleSecretRoom1A::~ModuleSecretRoom1A() {

}

bool ModuleSecretRoom1A::Start() {
	Room1A = App->textures->Load("Assets/Background/Secret_Rooms/1-1/Commando 1-A.png");
	items = App->textures->Load("Assets/Sprites/items&HUD&snake.png");

	check_audio = true;

	App->collision->Enable();
	//App->particles->Enable();
	//App->particlesenemies->Enable();
	//App->particlesgrenade->Enable();
	//App->particlesgrenade1->Enable();
	App->player->Enable();
	if (App->player2->twoplayerson == true)
	App->player2->Enable();
	App->enemies->Enable();
	App->UI->Enable();

	item.PushBack({ 4, 155, 14, 14 });

	hits = 0;

	App->player->current_animation = &App->player->forward;
	App->player->stairsDown = true;
	App->player->move = true;

	//Camera and player parametres
	App->player->position.x = SCREEN_WIDTH / 2;
	App->player->position.y = 185;
	App->player2->position.y = 160;
	App->scene_1->current_start_pos = 0;
	App->render->camera.y = 0;
	App->scene_1->cont = 0;

	//COLLIDERS
	App->collision->AddCollider({ 18,30, 15, 123 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,151, 16, 71 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,216, 255, 8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 224,30, 16, 112 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 240,141, 16, 74 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 32,31, 132, 12 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 189,26, 35, 17 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 167, 24, 15, 8 }, COLLIDER_SECRET_ROOM, this);

	//Items
	App->collision->AddCollider({ 52, 52, 14, 14 }, COLLIDER_ITEM, this);

	//ENEMIES
	App->enemies->AddEnemy(ENEMY_TYPES::PRISONER, 49, 41);

	return true;
}
update_status ModuleSecretRoom1A::Update() {

	App->render->Blit(Room1A, w, h, &background);


	if (check_audio) {
		App->audio->play_music10();
		check_audio = false;
	}


	current_animation = &item;
	r = current_animation->GetCurrentFrame();

	if (hits >= 30 && not_blit == false) {
		App->render->Blit(items, 50, 53, &r);
	}

	if (App->input->keyboard[SDL_SCANCODE_1] == 1 && KEY_DOWN) {
		App->render->UP = false;

		App->scene_1->start = false;
		App->scene_1->start1 = false;
		App->scene_1->start2 = true;
		App->scene_1->start3 = false;
		App->scene_1->start4 = false;
		App->scene_1->start5 = false;

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
	App->textures->Unload(items);

	App->UI->Disable();
	App->enemies->Disable();
	App->player->Disable();
	if (App->player2->twoplayerson == true)
	App->player2->Disable();
	//App->particlesgrenade1->Disable();
	//App->particlesgrenade->Disable();
	//App->particlesenemies->Disable();
	//App->particles->Disable();
	App->collision->Disable();

	return true;
}

void ModuleSecretRoom1A::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == COLLIDER_ITEM && c2->type == COLLIDER_PLAYER_SHOT) {
		hits++;
	}

	if (hits >= 30 && c1->type == COLLIDER_ITEM && c2->type == COLLIDER_PLAYER) {
		c1->to_delete = true;
		not_blit = true;
		App->UI->score += 10000;



		App->audio->play_fx7();
	}
}