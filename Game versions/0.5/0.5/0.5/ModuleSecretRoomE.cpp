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
#include "ModuleSecretRoomE.h"
#include "ModuleScene1.h"

ModuleSecretRoomE::ModuleSecretRoomE() {

}
ModuleSecretRoomE::~ModuleSecretRoomE() {

}

bool ModuleSecretRoomE::Start() {
	RoomE = App->textures->Load("Assets/Background/Secret_Rooms/1-1/1-E.png");
	background.x = 0;
	background.y = 0;
	background.w = 256;
	background.h = 224;

	App->render->camera.y = 0;


	App->player->Disable();
	App->collision->Disable();

	App->collision->Enable();
	App->player->Enable();
	App->UI->Enable();

	App->player->position.y = 170;
	
	App->collision->AddCollider({ 0,0, 256, 31 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,31, 116, 17 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 141,31, 115, 16 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 239,47, 16, 177 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 192,71, 49, 50 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 96,87, 63, 53 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,38, 16, 186 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,216, 256, 8 }, COLLIDER_WALL, this);



	return true;
}
update_status ModuleSecretRoomE::Update() {
	App->render->Blit(RoomE, w, h, &background);

	return UPDATE_CONTINUE;
}
bool ModuleSecretRoomE::CleanUp() {
	App->textures->Unload(RoomE);

	return true;
}