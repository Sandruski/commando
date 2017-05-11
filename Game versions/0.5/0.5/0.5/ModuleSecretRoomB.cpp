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

	App->render->camera.y = 0;


	App->player->Disable();
	App->collision->Disable();


	App->collision->Enable();
	App->player->Enable();
	App->UI->Enable();

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

	return UPDATE_CONTINUE;
}
bool ModuleSecretRoomB::CleanUp(){
	App->textures->Unload(RoomB);

	return true;
}
