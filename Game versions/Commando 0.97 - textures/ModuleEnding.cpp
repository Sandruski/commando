#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleScene1.h"
#include "ModuleMenu.h"
#include "ModuleEnding.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"
#include "ModuleEND.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleParticlesEnemies.h"
#include "ModuleTEX.h"
#include "ModuleParticlesGrenade.h"
#include "ModuleParticlesGrenade1.h"
#include "ModuleParticles.h"
#include "ModuleCinematic.h"
#include "ModuleSecretRoomC.h"
#include "ModuleUI.h"
#include <windows.h>
#include "ModuleEndinglvl1.h"

ModuleEnding::ModuleEnding()
{
	background2.x = 0;
	background2.y = 0;
	background2.w = 256;
	background2.h = 224;
}

ModuleEnding::~ModuleEnding()
{}

// Load assets
bool ModuleEnding::Start()
{
	LOG("Loading ending scene");
	App->render->camera.y = 0;
	Gameover = App->textures->Load("Assets/Sprites/gameover.png");



	//Initialize audio
	check_audio = true;
	check_audio1 = true;

	return true;
}

// UnLoad assets
bool ModuleEnding::CleanUp()
{
	LOG("Unloading ending scene");

	App->player->play_ending = false;
	App->scene_1->play_win = false;
	App->textures->Unload(Gameover);



	return true;
}

// Update: draw background
update_status ModuleEnding::Update()
{
	update_status ret = UPDATE_CONTINUE;


	if (App->fade->on == this && yeah == true) {
		cont = 0;
		yeah = false;
	}

	if (App->player2->twoplayerson){
		App->player->move2 = true;
		App->player2->move2 = true;
	}

	cont++;

	//win
	if (check_audio && App->scene_1->play_win == true) {
		App->audio->play_music4();
		check_audio = false;
		App->player->GunPowerUp = false;
		App->roomC->loop = false;
	}

	//lose
	else if (App->player->play_ending == true) {
		if (check_audio1) {
			App->audio->play_music5();
			check_audio1 = false;
		}
		App->render->Blit(Gameover, 0, 0, &background2);
	}


	if (cont == 205) {
		if(App->scene_1->play_win == false)
		App->fade->FadeToBlack(this, App->Menu, 1);
		else
			App->fade->FadeToBlack(this, App->EndingLvl1, 1);
		yeah = true;
	}


	return ret;
}