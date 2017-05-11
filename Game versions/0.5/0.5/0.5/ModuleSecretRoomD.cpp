#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSecretRoomD.h"
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

	App->player->Disable();
	App->collision->Disable();

	App->collision->Enable();
	App->player->Enable();
	App->UI->Enable();

	App->render->camera.y = -3 * SCREEN_HEIGHT;
	App->player->position.y = 370;

	return true;
}
update_status ModuleSecretRoomD::Update() {
	App->render->Blit(RoomD, w, h, &background);

	return UPDATE_CONTINUE;
}
bool ModuleSecretRoomD::CleanUp() {
	App->textures->Unload(RoomD);

	return true;
}
