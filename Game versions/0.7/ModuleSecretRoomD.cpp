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
#include "ModuleScene1.h"
#include "ModuleUI.h"
#include <windows.h>

ModuleSecretRoomD::ModuleSecretRoomD() {

}
ModuleSecretRoomD::~ModuleSecretRoomD() {

}

bool ModuleSecretRoomD::Start() {
	RoomD = App->textures->Load("Assets/Background/Secret_Rooms/1-1/salasecretea1-D.png");
	background.x = 0;
	background.y = 0;
	background.w = 256;
	background.h = 447;

	App->collision->Enable();
	App->player->Enable();
	App->UI->Enable();
	App->enemies->Enable();

	App->player->current_animation = &App->player->forward;

	check_player = 0;

	//Camera and player parametres
	App->player->position.x = SCREEN_WIDTH / 2;
	App->player->position.y = 410;
	App->scene_1->current_start_pos = SCREEN_HEIGHT;
	App->render->camera.y = -3 * SCREEN_HEIGHT;
	App->scene_1->cont = 0;

	//ENEMIES
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 20, 247);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 21, 232);

	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 214, 283);

	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 213, 193);

	return true;
}
update_status ModuleSecretRoomD::Update() {
	App->render->Blit(RoomD, w, h, &background);

	//Move camera
	if (App->player->position.y <= 230 && App->render->camera.y < 0) {
		check_player++;

		if (check_player % 2 == 0) {
			App->player->position.y--;
		}

		App->player->move = false;
		App->scene_1->cont += 2;
		App->player->current_animation = &App->player->forward;
		App->player->forward.Start();
		App->render->camera.y += 6;
	}
	else {
		App->player->forward.Stop();
		App->player->move = true;
	}
	//

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
		App->fade->FadeToBlack(this, App->scene_1, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_5] == 1 && KEY_DOWN) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->roomE, 1);
	}

	return UPDATE_CONTINUE;
}
bool ModuleSecretRoomD::CleanUp() {
	App->textures->Unload(RoomD);

	App->enemies->Disable();
	App->UI->Disable();
	App->player->Disable();
	App->collision->Disable();

	return true;
}
