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



	return true;
}
update_status ModuleSecretRoom1A::Update() {
	App->render->Blit(Room1A, w, h, &background);

	return UPDATE_CONTINUE;
}
bool ModuleSecretRoom1A::CleanUp() {
	App->textures->Unload(Room1A);

	return true;
}