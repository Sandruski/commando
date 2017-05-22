#include "Application.h"
#include "ModuleUI.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "GrenadesB.h"
#include "ItemsEnemies.h"
#include "ItemsEnemies2.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "Enemy.h"
#include "Soldier_Rifle.h"
#include "Soldier_Grenade.h"
#include "Soldier_Knife.h"
#include "Soldier.h"
#include "Soldier_Shield.h"
#include "ModuleScene1.h"
#include "Crazy_Green.h"
#include "ModuleAudio.h"
#include "Prisoner.h"
#include "PrisonerPoints.h"
#include "SoldierPrisoner.h"
#include <time.h>

#define SPAWN_MARGIN 50

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	
	sprites = App->textures->Load("Assets/Sprites/spritesheet_humanos.png");



	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (abs(queue[i].y * SCREEN_SIZE) < App->render->camera.y + (App->render->camera.h * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].y * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Move();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Draw(sprites);

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if ((enemies[i]->position.y > ((App->scene_1->current_start_pos + 114) - App->scene_1->cont + 88) + SPAWN_MARGIN) || enemies[i]->Esperanza == false)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.y * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = ENEMY_TYPES::NO_TYPE;
			queue[i].x = NULL;
			queue[i].y = NULL;
		}

		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{

		switch (info.type)
		{
		case ENEMY_TYPES::SOLDIER_RIFLE:
			enemies[i] = new Enemy_SoldierRifle(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::SOLDIER_RIFLE;
			enemies[i]->Esperanza = true;
			break;
		case ENEMY_TYPES::SOLDIER_GRENADE:
			enemies[i] = new Enemy_SoldierGrenade(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::SOLDIER_GRENADE;
			enemies[i]->Esperanza = true;
			break;
		case ENEMY_TYPES::SOLDIER_KNIFE:
			enemies[i] = new Enemy_SoldierKnife(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::SOLDIER_KNIFE;
			enemies[i]->Esperanza = true;
			break;
		case ENEMY_TYPES::SOLDIER:
			enemies[i] = new Enemy_Soldier(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::SOLDIER;
			enemies[i]->Esperanza = true;
			break;
		case ENEMY_TYPES::SOLDIER_SHIELD:
			enemies[i] = new Enemy_SoldierShield(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::SOLDIER_SHIELD;
			enemies[i]->Esperanza = true;
			break;
		case ENEMY_TYPES::CRAZY_GREEN:
			enemies[i] = new Enemy_CrazyGreen(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::CRAZY_GREEN;
			enemies[i]->Esperanza = true;
			break;
		case ENEMY_TYPES::PRISONER:
			enemies[i] = new Enemy_Prisoner(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::PRISONER;
			enemies[i]->Esperanza = true;
			break;
		case ENEMY_TYPES::PRISONERPOINTS:
			enemies[i] = new Enemy_PrisonerPoints(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::PRISONERPOINTS;
			enemies[i]->Esperanza = true;
			break;
		case ENEMY_TYPES::SOLDIERPRISONER:
			enemies[i] = new Enemy_SoldierPrisoner(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::SOLDIERPRISONER;
			enemies[i]->Esperanza = true;
			break;
		case ENEMY_TYPES::GRENADE:
			enemies[i] = new GrenadesB(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::GRENADE;
			enemies[i]->Esperanza = true;
			break;
		case ENEMY_TYPES::ITEM1:
			enemies[i] = new ItemsEnemies(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::ITEM1;
			enemies[i]->Esperanza = true;
			break;
		case ENEMY_TYPES::ITEM2:
			enemies[i] = new ItemsEnemies2(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::ITEM2;
			enemies[i]->Esperanza = true;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (c1->type == COLLIDER_ITEM) { //GRENADES
			if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1) {

				enemies[i]->OnCollision(c1, c2);
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
		}

		if (c1->type == COLLIDER_ITEM1) { //ITEMSENEMIES
			if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1) {

				enemies[i]->OnCollision(c1, c2);
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
		}


		if (c1->type == COLLIDER_PRISONER) { //PRISONERS
			if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1) {
				enemies[i]->OnCollision(c2, c1);
				App->audio->play_fx8();
			}
		}

		else if (c2->type != COLLIDER_WALL) {
			if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
			{

				if (c2->type == COLLIDER_END_OF_GRENADE && enemies[i]->type == ENEMY_TYPES::SOLDIER_SHIELD) {
					App->UI->score += 150;
					enemies[i]->OnCollision(c1, c2);
					c1->to_delete = true;
					App->audio->play_fx4();
				}

				else if (c2->type == COLLIDER_PLAYER_SHOT && enemies[i]->type == ENEMY_TYPES::SOLDIER_SHIELD){}

				else if (c2->type == COLLIDER_FOLLOW && enemies[i]->type == ENEMY_TYPES::SOLDIER) {
					enemies[i]->OnCollision(c1, c2);
				}

				else if (c1->type == COLLIDER_ENEMY  && c2->type != COLLIDER_PLAYER) {
					if (c2->type == COLLIDER_PLAYER_SHOT) {
						if (enemies[i]->type == ENEMY_TYPES::SOLDIER)
							App->UI->score += 150;
						else
							App->UI->score += 75;
					}
				
					else {
						if (enemies[i]->type == ENEMY_TYPES::SOLDIER)
							App->UI->score += 300;
						else
							App->UI->score += 150;
					}
					enemies[i]->OnCollision(c1, c2);
					delete enemies[i];
					enemies[i] = nullptr;
					break;
					App->audio->play_fx4();
				}
				/*if (dieE == true) {
				delete enemies[i];
				enemies[i] = nullptr;
				break;
				}*/
			}
		}

		/*else if (c2->type == COLLIDER_WALL && c1->type == COLLIDER_ENEMY) {
			if (enemies[i] != nullptr) {
				if (enemies[i]->type == ENEMY_TYPES::SOLDIER)
					enemies[i]->OnCollision(c1, c2);
			}
		}*/
	


	}
	

		


}