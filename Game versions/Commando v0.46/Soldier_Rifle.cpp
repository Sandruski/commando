#include "Application.h"
#include "Soldier_Rifle.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleParticlesEnemies.h"
#include <stdlib.h>
#include <time.h>


Enemy_SoldierRifle::Enemy_SoldierRifle(int x, int y) : Enemy(x, y)
{
	//ANIMATION TURN (SOLDIER WITH RIFLE)
	center.PushBack({ 107, 110, 18, 18 });
	left.PushBack({ 142, 110, 18, 18 });
	more_left.PushBack({ 159, 110, 18, 18 });
	right.PushBack({ 125, 110, 18, 18 });
	more_right.PushBack({ 177, 110, 18, 18 });

	center.speed = 0.1f;
	left.speed = 0.1f;
	more_left.speed = 0.1f;
	right.speed = 0.1f;
	more_right.speed = 0.1f;

	animation = &center;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void Enemy_SoldierRifle::Move()
{
	//MOVEMENT
	if (App->player->position.x <= position.x - 22) {
		animation = &more_left;
	}
	else if (App->player->position.x >= position.x + 22) {
		animation = &more_right;
	}
	else if (App->player->position.x > position.x - 22 && App->player->position.x < position.x - 2) {
		animation = &left;
	}
	else if (App->player->position.x < position.x + 22 && App->player->position.x > position.x + 2) {
		animation = &right;
	}
	else if (App->player->position.x >= position.x - 2 && App->player->position.x <= position.x + 2) {
		animation = &center;
	}

	//SHOT

	num_shots = rand() % 4;

	if (rand1 == 3 && App->player->position.y > position.y + 24) {

		for (int i = 0; i <= 4; i++) {
			App->particlesenemies->AddParticle(App->particlesenemies->bala, position.x, position.y, COLLIDER_NONE, NULL); //position.y+30+space
																														  //space = rand() % 10 + 5;
		}

		enemyplayer.x = App->player->position.x - position.x;
		enemyplayer.y = abs(position.y) - abs(App->player->position.y);

		App->particlesenemies->bala.speed.x = (enemyplayer.x * 0.01f);
		App->particlesenemies->bala.speed.y = (enemyplayer.y * 0.01f);

		App->particlesenemies->bala.position.x = int(position.x + App->particlesenemies->bala.speed.x);
		App->particlesenemies->bala.position.y = int(position.y + App->particlesenemies->bala.speed.y);


		//y = abs(App->player->position.y) - abs(position.y);
		//x = App->player->position.x - position.x;

		//App->particlesenemies->bala.speed.y = sin(atan(y / x)) * 2;
		//App->particlesenemies->bala.speed.x = cos(atan(y / x)) * 2;



		space = 0;

	}

	rand1 = rand() % 200;

	//Change of behaviour. Soldier walks backwards
	/*
	if (App->player->position.y <= position.y - 24) {

	}
	*/

}