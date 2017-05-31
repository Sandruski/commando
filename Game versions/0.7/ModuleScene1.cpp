#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleScene1.h"
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
#include "ModuleSaveData.h"
#include "ModuleSecretRoom1A.h"
#include "ModuleSecretRoomB.h"
#include "ModuleSecretRoomC.h"
#include "ModuleSecretRoomD.h"
#include "ModuleSecretRoomE.h"
#include <windows.h>
#include <fstream>
#include <iostream>
#include "ModuleEndinglvl1.h"
#include "ModuleCinematicRadio.h"

using namespace std;

ModuleScene1::ModuleScene1()
{
	door.PushBack({ 89, 89, 82, 59 });

	ammo_grenades_colours.PushBack({ 179, 126, 33, 18 });
	ammo_grenades_colours.PushBack({ 179, 152, 33, 18 });
	ammo_grenades_colours.PushBack({ 179, 173, 33, 18 });
	ammo_grenades_colours.PushBack({ 179, 298, 33, 18 });
	ammo_grenades_colours.speed = 0.2f;

	win1.PushBack({ 0, 0, 27, 11 });

	ammo_specialgrenade1.PushBack({ 76, 228, 13, 14 });
	ammo_specialgrenade1.PushBack({ 56, 228, 13, 14 });
	ammo_specialgrenade1.speed = 0.2f;

	moto_go.PushBack({ 20, 22, 47, 23 });
	moto_go.speed = 0.2f;

	moto_stop.PushBack({ 73, 17, 47, 29 });
	moto_stop.PushBack({ 130, 19, 47, 26 });
	moto_stop.PushBack({ 187, 17, 47, 28 });
	moto_stop.speed = 0.1f;

}

ModuleScene1::~ModuleScene1()
{}

// Load assets
bool ModuleScene1::Start()
{

	LOG("Loading 1st scene");
	moto = App->textures->Load("Assets/Sprites/vehicles.png");
	items = App->textures->Load("Assets/Sprites/items&HUD&snake.png");
	graphics = App->textures->Load("Assets/Background/1-1.png");
	win = App->textures->Load("Assets/Sprites/win.png");
	end_door = App->textures->Load("Assets/Sprites/door.png");

	background.x = 0;
	background.y = 0;
	background.w = 256;
	background.h = 2880;

	contcamera1 = 0;
	contcamera2 = 0;

	dead = false;
	first = true;

	Secret_Room.x = 110;
	Secret_Room.y = 125;
	Secret_Room.w = 16;
	Secret_Room.h = 16;

	App->collision->Enable();
	App->particles->Enable();
	App->particlesenemies->Enable();
	App->particlesgrenade->Enable();
	App->particlesgrenade1->Enable();
	App->player->Enable();
	if (App->player2->twoplayerson == true)
		App->player2->Enable();
	App->enemies->Enable();
	App->UI->Enable();

	App->player->check_grenade = 1;
	App->enemies->dieE = 0;
	App->player->non_grenade = false;
	App->player->move = true;
	App->player->stairsUp = true;
	App->player->enemyB = true;
	App->player->waterB = true;
	for (int i = 0; i <= 9; i++) {
		App->player->detectionitem[i] = false;
	}
	App->player->current_animation = &App->player->idleF;
	cont6 = false;
	cont5 = 0;

	//Initialize audio
	check_audio = true;
	check_audio1 = true;
	check_audio2 = true;
	check_audio3 = true;

	//Initialize moto
	w = 0;
	h = SCREEN_HEIGHT - 2880;
	w_m = 255, h_m = 20;
	contador = 0;

	//Initialize camera for respawns
	if (start1) {
		start1 = true;
		start2 = false;
		start3 = false;
		start4 = false;
		start5 = false;
		App->player->position.x = 130;
		App->player->position.y = 110;
		current_start_pos = 0;

		App->render->camera.y = 0;
	}
	else if (start2) {
		start1 = false;
		start2 = true;
		start3 = false;
		start4 = false;
		start5 = false;
		App->player->position.x = 114;
		App->player->position.y = 2294 - 2656;
		current_start_pos = 2294 - 2656 - 114;

		App->render->camera.y = ((abs(App->player->position.y)) + 114) * 3;
	}
	else if (start3) {
		start1 = false;
		start2 = false;
		start3 = true;
		start4 = false;
		start5 = false;
		App->player->position.x = 127;
		App->player->position.y = 1836 - 2656;
		current_start_pos = 1836 - 2656 - 114;

		App->render->camera.y = ((abs(App->player->position.y)) + 114) * 3;
	}
	else if (start4) {
		start1 = false;
		start2 = false;
		start3 = false;
		start4 = true;
		start5 = false;
		App->player->position.x = 122;
		App->player->position.y = 882 - 2656;
		current_start_pos = 882 - 2656 - 114;

		App->render->camera.y = ((abs(App->player->position.y)) + 114) * 3;
	}
	else if (start5) {
		start1 = false;
		start2 = false;
		start3 = false;
		start4 = false;
		start5 = true;
		App->player->position.x = 122;
		App->player->position.y = 395 - 2656;
		current_start_pos = 395 - 2656 - 114;

		App->render->camera.y = ((abs(App->player->position.y)) + 114) * 3;
	}

	App->render->camera.x = 0;
	cont = 0;

	App->player->move2 = true;

	//Colliders
	App->collision->AddCollider({ 133,2817 - 2656,20,23 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 153,2802 - 2656,18,17 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 171,2817 - 2656,20,23 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 22,2769 - 2656,20,20 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 193,2705 - 2656,61,26 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 84,2640 - 2656,29,25 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,2642 - 2656,43,25 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 133,2594 - 2656,19,23 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 170,2594 - 2656,21,23 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 150,2577 - 2656,20,24 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 84,2528 - 2656, 24, 22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 201,2486 - 2656,56,54 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 5,2418 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 43,2418 - 2656,19,23 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 22,2402 - 2656,20,24 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 133,2385 - 2656,55,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 85,2339 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 149,2289 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,2262 - 2656,57,50 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 213,2226 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 201,1926 - 2656,53,56 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 204,1749 - 2656,53,56 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,1989 - 2656,121,51 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 256,1927 - 2656,58,48 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 71,1861 - 2656,81,51 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 256,1750 - 2656,57,50 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,1702 - 2656,57,53 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 70,1698 - 2656,20,23 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 108,1698 - 2656,20,23 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 86,1682 - 2656,20,23 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 22,1538 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 149,1538 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 86,1472 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 195,1470 - 2656,57,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,1343 - 2656,100,81 }, COLLIDER_WALL, this);  //Pont
	App->collision->AddCollider({ 156,1343 - 2656,100,81 }, COLLIDER_WALL, this); //Pont
																				  //-------------- Pedres
	App->collision->AddCollider({ 0,1204 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 49,1140 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 161,1140 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 196,1087 - 2656,56,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 33,1060 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 113,1029 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 178,997 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,1007 - 2656,56,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 160,933 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 16,853 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 113,853 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 209,853 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 210,718 - 2656,45,81 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 6,737 - 2656,21,19 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 44,737 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 22,721 - 2656,24,22 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 67,752 - 2656,56,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 147,671 - 2656,73,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 209,1456 - 2656,19,18 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,639 - 2656,56,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 100,575 - 2656,56,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,511 - 2656,75,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 212,389 - 2656,45,72 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,420 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 65,373 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 129,341 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 193,309 - 2656,32,15 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 131,287 - 2656,56,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0,116 - 2656,40,119 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 211,102 - 2656,47,119 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 35,79 - 2656,56,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 163,79 - 2656,56,8 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 0, 0 - 2656,94,39 }, COLLIDER_WALL, this); //Muralla
	App->collision->AddCollider({ 161,0 - 2656,95,39 }, COLLIDER_WALL, this); //Muralla

																			  //AIGUA

	App->collision->AddCollider({ 0,2466 - 2656,57,40 }, COLLIDER_WATER, this);
	App->collision->AddCollider({ 40,1248 - 2656,47,27 }, COLLIDER_WATER, this);
	App->collision->AddCollider({ 168,1202 - 2656,94,75 }, COLLIDER_WATER, this);
	App->collision->AddCollider({ 0,241 - 2656,90,59 }, COLLIDER_WATER, this);

	//ITEMS

	App->collision->AddCollider({ 157, 2473 - 2656,13,7 }, COLLIDER_ITEM, this);
	App->collision->AddCollider({ 169, 2465 - 2656,13,7 }, COLLIDER_ITEM, this);

	App->collision->AddCollider({ 37, 1945 - 2656,13,7 }, COLLIDER_ITEM, this);
	App->collision->AddCollider({ 49, 1937 - 2656,13,7 }, COLLIDER_ITEM, this);

	App->collision->AddCollider({ 34, 953 - 2656,13,7 }, COLLIDER_ITEM, this);
	App->collision->AddCollider({ 46, 945 - 2656,13,7 }, COLLIDER_ITEM, this);

	App->collision->AddCollider({ 48, 715 - 2656,13,7 }, COLLIDER_ITEM, this);
	App->collision->AddCollider({ 60, 707 - 2656,13,7 }, COLLIDER_ITEM, this);

	App->collision->AddCollider({ 5, 473 - 2656,13,7 }, COLLIDER_ITEM, this);
	App->collision->AddCollider({ 17, 465 - 2656,13,7 }, COLLIDER_ITEM, this);

	App->collision->AddCollider({ 157, 227 - 2656,13,7 }, COLLIDER_ITEM, this);
	App->collision->AddCollider({ 171, 219 - 2656,13,7 }, COLLIDER_ITEM, this);


	App->collision->AddCollider({ 151, 2625 - 2656,17,17 }, COLLIDER_ITEM, this); //Granades
	App->collision->AddCollider({ 185, 1149 - 2656,17,17 }, COLLIDER_ITEM, this);


	App->collision->AddCollider({ 150, 2370 - 2656,16,16 }, COLLIDER_SECRET_ROOM, this); //Secret Rooms
	App->collision->AddCollider({ 9, 2051 - 2656,16,16 }, COLLIDER_SECRET_ROOM, this);
	App->collision->AddCollider({ 217, 1426 - 2656,16,16 }, COLLIDER_SECRET_ROOM, this);
	App->collision->AddCollider({ 121, 1056 - 2656,16,16 }, COLLIDER_SECRET_ROOM, this);
	App->collision->AddCollider({ 233, 522 - 2656,16,16 }, COLLIDER_SECRET_ROOM, this);

	//botiquins
	App->collision->AddCollider({ 190, 150 ,9,9}, COLLIDER_TOREVIVE, this);
	App->collision->AddCollider({ 102, 2212 - 2656,9,9 }, COLLIDER_TOREVIVE, this);
	App->collision->AddCollider({ 84, 1502 - 2656,9,9}, COLLIDER_TOREVIVE, this);
	App->collision->AddCollider({ 243, 708 - 2656,9,9}, COLLIDER_TOREVIVE, this);

	App->render->Blit(App->player2->graphics, 198, 150, &App->player2->torevive2);
	App->render->Blit(App->player2->graphics, 102, 2212 - 2656, &App->player2->torevive2);
	App->render->Blit(App->player2->graphics, 84, 1502 - 2656, &App->player2->torevive2);
	App->render->Blit(App->player2->graphics, 243, 708, &App->player2->torevive2);
	//ENEMIES
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 150, 2366 - 2656); //positiony = 1375-2656
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_GRENADE, 227, 1449 - 2656);

	//Soldier rifle behind stone
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 167, 1127 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 53, 1127 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 37, 1047 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 118, 1015 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 182, 983 - 2656);

	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 166, 919 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 117, 835 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 7, 835 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 234, 835 - 2656);


	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 6, 405 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 70, 359 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 134, 327 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 199, 295 - 2656);

	//Soldier rifle behind barricade
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 89, 736 - 2656);

	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 154, 657 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 184, 657 - 2656);

	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 23, 624 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 119, 559 - 2656);

	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 19, 497 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 55, 497 - 2656);

	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_RIFLE, 152, 279 - 2656);

	//Soldier grenade behind barricade
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_GRENADE, 213, 1065 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_GRENADE, 21, 984 - 2656);

	//Soldier shield
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_SHIELD, 111, 35 - 2656);

	//Crazy green soldier
	App->enemies->AddEnemy(ENEMY_TYPES::CRAZY_GREEN, 121, 70 - 2656);

	//Prisoners
	App->enemies->AddEnemy(ENEMY_TYPES::PRISONER, 15, 752 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::PRISONER, 47, 756 - 2656);

	//PrisonerPoints
	App->enemies->AddEnemy(ENEMY_TYPES::PRISONERPOINTS, 58, 1667 - 2656);

	//SoldierPrisoner
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIERPRISONER, 44, 1669 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIERPRISONER, 72, 1665 - 2656);

	//SoldierKnife
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_KNIFE, 34, 2072 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER_KNIFE, 239, 2075 - 2656);

	//SOLDIER
	
	//Path
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 62, 2506 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 240, 2550 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 239, 2408 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 118, 2154 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 254, 1693 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 224, 1624 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 225, 1023 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 142, 896 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 242, 699 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 240, 688 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 225, 538 - 2656);
	

	
	//Path2
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 14, 2579 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 6, 2245 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 73, 2212 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 45, 1962 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 30, 1619 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 10, 621 - 2656);

	//Path3
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 29, 2348 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 167, 2230 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 143, 1970 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 168, 1500 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 62, 812 - 2656);
	

	
	//Path_Final_Battle
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 40, 111 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 170, 104 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 124, -2 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 108, -5 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 130, -8 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 122, 0 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 35, 120 - 2656);

	//Path_Final_Battle1
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 49, 125 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 116, 57 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 124, 98 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 108, 55 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 130, 42 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 119, 20 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 133, 30 - 2656);

	//Path_Final_Battle2
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 123, 35 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 116, 1 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 124, 2 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 108, 7 - 2656);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 130, 4 - 2656);
	
	return true;

}

bool ModuleScene1::CleanUp()
{
	LOG("Unloading 1st scene");
	App->textures->Unload(graphics);
	App->textures->Unload(moto);
	App->textures->Unload(items);
	App->textures->Unload(win);
	App->textures->Unload(end_door);

	App->UI->Disable();
	App->enemies->Disable();
	App->player->Disable();
	App->player2->Disable();
	App->particlesgrenade1->Disable();
	App->particlesgrenade->Disable();
	App->particlesenemies->Disable();
	App->particles->Disable();
	App->collision->Disable();

	return true;
}

// Update: draw background
update_status ModuleScene1::Update()
{
	update_status ret = UPDATE_CONTINUE;

	///////////////////////////////////////////////////////////////////////////////
	//ENEMIES

	if (App->player->position.y <= 2720 - 2656 && App->player->position.y >= 2352 - 2656) {
		E1 = true;
	}
	else {
		E1 = false;
	}

	if (E1) {
		contenemy1++;

		if (contenemy1 == 20) {
			App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER2, 247, 2498 - 2656);
		}
		else if (contenemy1 == 150) {
			App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER2, 247, 2498 - 2656);
			App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER2, 247, 2499 - 2656);
		}
		else if (contenemy1 == 300) {
			App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER2, 247, 2498 - 2656);
		}
		else if (contenemy1 == 320) {
			App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER2, 247, 2499 - 2656);
		}
		else if (contenemy1 == 420) {
			App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER2, 247, 2499 - 2656);
		}
		else if (contenemy1 == 500) {
			App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER2, 247, 2499 - 2656);
		}
		else if (contenemy1 == 600) {
			App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER2, 247, 2499 - 2656);
			App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER2, 247, 2498 - 2656);
		}
		else if (contenemy1 == 800) {
			App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER2, 247, 2498 - 2656);
		}

		if (contenemy1 == 1000) {
			contenemy1 = 0;
		}
	}


	if (App->player->position.y <= 2516 - 2656 && App->player->position.y >= 2100 - 2656) {
		E2 = true;
	}
	else {
		E2 = false;
	}


	if (E2) {
		contenemy2++;

		if (contenemy2 == 20) {
			App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER2, 5, 2272 - 2656);
		}
		else if (contenemy2 == 100) {
			App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER2, 5, 2271 - 2656);
		}
		else if (contenemy2 == 300) {
			App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER2, 5, 2272 - 2656);
		}
		else if (contenemy2 == 420) {
			App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER2, 5, 2272 - 2656);
		}
		else if (contenemy2 == 500) {
			App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER2, 5, 2271 - 2656);
		}
		else if (contenemy2 == 650) {
			App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER2, 5, 2272 - 2656);
		}
		else if (contenemy2 == 800) {
			App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER2, 5, 2271 - 2656);
		}

		if (contenemy2 == 1000) {
			contenemy2 = 0;
		}
	}







	///////////////////////////////////////////////////////////////////////////////


	if (check_audio) {
		App->audio->play_music2();
		check_audio = false;
	}

	//CAMERA
	//middle screen (where camera goes up) = 110 - cont
	//bottom screen = 110 - cont + 88
	if ((App->player->position.y == (110 - cont) || App->player->position.y == (2294 - 2656 - cont) ||
		App->player->position.y == (1836 - 2656 - cont) || App->player->position.y == (882 - 2656 - cont) ||
		App->player->position.y == (379 - 2656 - cont))
		&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && App->render->camera.y < ((2880 - SCREEN_HEIGHT)*SCREEN_SIZE) - speed) {
		contcamera1++;
		App->render->camera.y += speed;
	}

	else if ((App->player2->position.y == (110 - cont) || App->player2->position.y == (2294 - 2656 - cont) ||
		App->player2->position.y == (1836 - 2656 - cont) || App->player2->position.y == (882 - 2656 - cont) ||
		App->player2->position.y == (379 - 2656 - cont))
		&& App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT && App->render->camera.y < ((2880 - SCREEN_HEIGHT)*SCREEN_SIZE) - speed) {
		contcamera2++;
		App->render->camera.y += speed;
	}
	cont = contcamera2 + contcamera1;
	//Animation* current_animation = &moto_stop;

	App->render->Blit(graphics, w, h, &background);

	current_animation = &ammo_grenades_colours;
	r = current_animation->GetCurrentFrame();
	if (App->player->detectionitem[1] == false)
	App->render->Blit(items, 153, 2464 - 2656, &r);
	if (App->player->detectionitem[2] == false)
	App->render->Blit(items, 33, 1936 - 2656, &r);
	if (App->player->detectionitem[4] == false)
	App->render->Blit(items, 30, 944 - 2656, &r);
	if (App->player->detectionitem[5] == false)
	App->render->Blit(items, 44, 706 - 2656, &r);
	if (App->player->detectionitem[6] == false)
	App->render->Blit(items, 1, 464 - 2656, &r);
	if (App->player->detectionitem[7] == false)
	App->render->Blit(items, 155, 218 - 2656, &r);

	current_animation = &ammo_specialgrenade1;
	r = current_animation->GetCurrentFrame();
	if (App->player->detectionitem[0] == false)
	App->render->Blit(items, 151, 2625 - 2656, &r);
	if (App->player->detectionitem[3] == false)
	App->render->Blit(items, 185, 1149 - 2656, &r);




	if(roomA == true)
		App->render->Blit(items, 150, 2372 - 2656, &Secret_Room);
	if (roomB == true)
		App->render->Blit(items, 9, 2051 - 2656, &Secret_Room);
	if (roomC == true)
		App->render->Blit(items, 217, 1426 - 2656, &Secret_Room);
	if (roomD == true)
		App->render->Blit(items, 121, 1056 - 2656, &Secret_Room);
	if (roomE == true)
		App->render->Blit(items, 233, 522 - 2656, &Secret_Room);

	
	
	//-2656
	if (App->player->position.y <= 1550 - 2656 && contador < 120) { /* && App->player->position.y >= 1300 - 2656 */
		if (w_m > 105) {
			if (check_audio1) {
				App->audio->play_fx9();
				check_audio1 = false;
			}
			current_animation = &moto_go;
			r = current_animation->GetCurrentFrame();
			App->render->Blit(moto, w_m, 1345 - 2656, &r);
			w_m--;
		}

		else if (w_m == 105) {
			current_animation = &moto_stop;
			r = current_animation->GetCurrentFrame();
			App->render->Blit(moto, w_m, 1345 - 2656, &r);
			contador++;
		}
	}

	else if (contador >= 120) {
		if (check_audio2) {
			App->audio->play_fx10();
			check_audio2 = false;
		}
		Animation* current_animation = &moto_go;
		r = current_animation->GetCurrentFrame();
		App->render->Blit(moto, w_m, 1345 - 2656, &r);
		w_m--;
	}
	
	//Secret rooms auto
	if (App->input->keyboard[SDL_SCANCODE_1] == KEY_DOWN && App->fade->IsFading() == false) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->room1A, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_2] == KEY_DOWN && App->fade->IsFading() == false) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->roomB, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_3] == KEY_DOWN && App->fade->IsFading() == false) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->roomC, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_4] == KEY_DOWN && App->fade->IsFading() == false) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->roomD, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_5] == KEY_DOWN && App->fade->IsFading() == false) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->roomE, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_8] == 1 && KEY_DOWN) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->EndingLvl1, 1);

	}

	//Respawns auto
	if (App->input->keyboard[SDL_SCANCODE_Z] == 1 && KEY_DOWN) {
		start = false;
		start1 = true;
		start2 = false;
		start3 = false;
		start4 = false;
		start5 = false;
		App->render->UP = false;
		App->fade->FadeToBlack(this, this, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_X] == 1 && KEY_DOWN) {
		start = false;
		start1 = false;
		start2 = true;
		start3 = false;
		start4 = false;
		start5 = false;
		App->render->UP = false;
		App->fade->FadeToBlack(this, this, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_C] == 1 && KEY_DOWN) {
		start = false;
		start1 = false;
		start2 = false;
		start3 = true;
		start4 = false;
		start5 = false;
		App->render->UP = false;
		App->fade->FadeToBlack(this, this, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_V] == 1 && KEY_DOWN) {
		start = false;
		start1 = false;
		start2 = false;
		start3 = false;
		start4 = true;
		start5 = false;
		App->render->UP = false;
		App->fade->FadeToBlack(this, this, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_B] == 1 && KEY_DOWN) {
		start = false;
		start1 = false;
		start2 = false;
		start3 = false;
		start4 = false;
		start5 = true;
		App->render->UP = false;
		App->fade->FadeToBlack(this, this, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_L] == 1 && KEY_DOWN) {
		App->fade->FadeToBlack(this, App->CinematicRadio, 1);

	}

	
	// end

	if (App->input->keyboard[SDL_SCANCODE_F9] == 1 && KEY_DOWN) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->Menu, 3);
	}

	if (App->player->position.y <= 60 - 2656 && winB == true) 
		cont6 = true;
	
	if (cont6 == true) {
		current_animation = &win1;
		r = current_animation->GetCurrentFrame();
		//App->render->Blit(win, 112, 60 - 2656, &r);
		cont5++;
	}
	if (cont5 == 20) {
		play_win = true;
		App->ending->cont = 0;
		start = true;
		App->fade->FadeToBlack(this, App->ending, 3);
		App->player->vides = 3;
	}
	cont8 = true;

	if (App->player->position.y == 119 - 2565) {
		App->audio->pause_music();
		if (check_audio3) {
			App->audio->play_music7();
			check_audio3 = false;
		}
	}

	if (cont8 == true) {
		if (cont7 == 20)
			App->fade->FadeToBlack(this, this, 3);
	}

	//end door opens when enemies start spawning
	if (App->render->camera.y == ((2880 - SCREEN_HEIGHT)*SCREEN_SIZE) - speed) {
		current_animation1 = &door;
		reee = current_animation1->GetCurrentFrame();

		App->render->Blit(end_door, 88, -2656, &reee);
	}



	//player walks towards the end door
	if (dead) {
		
		if (first) {
			if (App->player->position.x < SCREEN_WIDTH / 2) {
				App->player->current_animation = &App->player->right;
				App->player->right.Start();

				App->player->position.x++;
			}
			else if (App->player->position.x > SCREEN_WIDTH / 2) {
				App->player->current_animation = &App->player->left;
				App->player->left.Start();

				App->player->position.x--;
			}

			if (App->player->position.x == SCREEN_WIDTH / 2)
				first = false;
		}

		if (!first) {
			App->player->position.y--;
			App->player->current_animation = &App->player->forward;
			App->player->forward.Start();
		}
	}
	//

	//botiquin
	if (App->player2->twoplayerson == true) {
		if(torevivecheck1 == false)
		App->render->Blit(App->player2->graphics, 190, 150, &App->player2->torevive2);
		if (torevivecheck2 == false)
		App->render->Blit(App->player2->graphics, 102, 2212 - 2656, &App->player2->torevive2);
		if (torevivecheck3 == false)
		App->render->Blit(App->player2->graphics, 84, 1502 - 2656, &App->player2->torevive2);
		if (torevivecheck4 == false)
		App->render->Blit(App->player2->graphics, 243, 708 - 2656, &App->player2->torevive2);
	}
	return ret;
}


void ModuleScene1::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == COLLIDER_SECRET_ROOM && c2->type == COLLIDER_END_OF_GRENADE){
		if (App->player->position.y < 2480 - 2656 && App->player->position.y > 2350 - 2656)
			roomA= true;
		if (App->player->position.y < 2145 - 2656 && App->player->position.y > 2000 - 2656) 
			roomB = true;
		if (App->player->position.y < 1520 - 2656 && App->player->position.y > 1400 - 2656) 
			roomC = true;
		if (App->player->position.y < 1160 - 2656 && App->player->position.y > 1000 - 2656) 
			roomD = true;
		if (App->player->position.y < 630 - 2656 && App->player->position.y > 475 - 2656) 
			roomE = true;
		}

	else if (c1->type == COLLIDER_TOREVIVE && c2->type == COLLIDER_PLAYER || c1->type == COLLIDER_TOREVIVE && c2->type == COLLIDER_PLAYER2) {
		App->player2->torevive++;
		if (App->player->position.y < 150 && App->player->position.y > 0)
			torevivecheck1 = true;
		if (App->player->position.y < 2212 - 2656 + 100 && App->player->position.y > 2212 - 2656 - 100)
			torevivecheck2 = true;
		if (App->player->position.y < 1502 - 2656 + 100 && App->player->position.y > 1502 - 2656 - 100)
			torevivecheck3 = true;
		if (App->player->position.y < 708 - 2656 + 100 && App->player->position.y > 708 - 2656 - 100)
			torevivecheck4 = true;
		App->collision->EraseCollider(c1);
	}
}

