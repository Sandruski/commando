#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSecretRoomC.h"
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
#include "ModuleScene1.h"
#include "ModuleCinematic.h"
#include "ModuleUI.h"
#include <windows.h>

ModuleSecretRoomC::ModuleSecretRoomC() {

}
ModuleSecretRoomC::~ModuleSecretRoomC() {

}

bool ModuleSecretRoomC::Start() {
	RoomC = App->textures->Load("Assets/Background/Secret_Rooms/1-1/salasecretea1-C.png");
	background.x = 0;
	background.y = 0;
	background.w = 256;
	background.h = 447;

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

	App->render->camera.y = -3 * SCREEN_HEIGHT;
	App->player->position.y = 370;

	return true;
}
update_status ModuleSecretRoomC::Update() {
	App->render->Blit(RoomC, w, h, &background);

	return UPDATE_CONTINUE;
}
bool ModuleSecretRoomC::CleanUp() {
	App->textures->Unload(RoomC);

	App->enemies->Disable();
	App->UI->Disable();
	App->player->Disable();
	App->collision->Disable();

	return true;
}
