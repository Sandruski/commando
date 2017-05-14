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
	App->player->Enable();
	App->UI->Enable();
	App->enemies->Enable();

	//Camera and player parametres
	App->player->position.x = 130;
	App->player->position.y = 110;
	App->scene_1->current_start_pos = 0;
	App->render->camera.y = 0;
	App->scene_1->cont = 0;

	App->collision->AddCollider({ 0,0, 256, 45 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 208,38, 48, 24 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 240,61, 16, 163 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,216, 242, 8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,38, 16, 186 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 15,72, 65, 50 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 208 ,60, 6, 26 }, COLLIDER_WALL, this);



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

	App->enemies->Disable();
	App->UI->Disable();
	App->player->Disable();
	App->collision->Disable();

	return true;
}
