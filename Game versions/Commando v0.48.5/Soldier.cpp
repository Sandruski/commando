#include "Application.h"
#include "Soldier.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "Path.h"
#include <stdlib.h>
#include <time.h>
#include "ModuleParticlesEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Enemy_Soldier::Enemy_Soldier(int x, int y) : Enemy(x, y)
{
	//ANIMATION MOVE (normal SOLDIER)
	//first sprite of an animation: soldier standing
	//second sprite of an animation: soldier walking

	up.PushBack({ 114, 82, 11, 21 });
	up.PushBack({ 128, 82, 11, 22 });

	down.PushBack({ 80, 82, 13, 23 });
	down.PushBack({ 232, 47, 13, 23 });

	left.PushBack({ 210, 82, 16, 22 });
	left.PushBack({ 228, 82, 16, 22 });

	right.PushBack({ 61, 82, 16, 22 });
	right.PushBack({ 42, 82, 16, 22 });

	up_left.PushBack({ 194, 82, 14, 22 });
	up_left.PushBack({ 6, 82, 16, 22 });

	up_right.PushBack({ 25, 82, 14, 22 });
	up_right.PushBack({ 175, 82, 16, 22 });

	down_left.PushBack({ 96, 82, 15, 22 });
	down_left.PushBack({ 213, 48, 15, 22 });

	down_right.PushBack({ 141, 82, 15, 22 });
	down_right.PushBack({ 158, 82, 15, 22 });

	
								
	up.speed = 0.1f;
	down.speed = 0.1f;
	left.speed = 0.1f;
	right.speed = 0.1f;
	up_left.speed = 0.1f;
	up_right.speed = 0.1f;
	down_left.speed = 0.1f;
	down_right.speed = 0.1f;


	//PATHS
	//fPoint speed, uint frames, Animation* animation = nullptr
	path.PushBack({ -0.5f, 0.5f }, 50);
	path.PushBack({ +0.5f, +0.5f }, 50);
	path.PushBack({ 0.0f, +0.5f }, 50);
	path.loop = false;

	animation = &up;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_Soldier::Move()
{
	if (path.Path1Finished() == false) {
		position = original_pos + path.GetCurrentPosition(&animation);
		save_step = path.GetCurrentPositionf(); //it returns an fPoint of the speed of the current step
	}
	else {
		//MOVEMENT
		enemyplayer2.x = (App->player->p1.x) - position.x;
		enemyplayer2.y = abs(position.y) - abs(App->player->p1.y);

		module = sqrt((pow(enemyplayer2.x, 2) + pow(enemyplayer2.y, 2)));

		enemyplayeru2.x = enemyplayer2.x / module;
		enemyplayeru2.y = enemyplayer2.y / module;

		position.x = (position.x + enemyplayeru2.x);
		position.y = ((position.y + 25) + enemyplayeru2.y);
	}
	//end_of_movement

	//ANIMATION CHANGE
	if (save_step.x == 0 && save_step.y > 0) {
		animation = &down;
	}
	else if (save_step.x == 0 && save_step.y < 0) {
		animation = &up;
	}
	else if (save_step.x > 0 && save_step.y == 0) {
		animation = &right;
	}
	else if (save_step.x < 0 && save_step.y == 0) {
		animation = &left;
	}
	else if (save_step.x > 0 && save_step.y > 0) {
		animation = &down_right;
	}
	else if (save_step.x < 0 && save_step.y > 0) {
		animation = &down_left;
	}
	else if (save_step.x > 0 && save_step.y < 0) {
		animation = &up_right;
	}
	else if (save_step.x < 0 && save_step.y < 0) {
		animation = &up_left;
	}
	//

	//SHOT
	/*
	num_shots = rand() % 4;

	if (rand1 == 3 && position.x > 0 && position.x < SCREEN_WIDTH) {

	for (int i = 0; i <= num_shots; i++) {
	App->particlesenemies->AddParticle(App->particlesenemies->bala, position.x, (position.y + 25), COLLIDER_ENEMY_SHOT, NULL); //position.y+30+space
	space = rand() % 10 + 5;
	}

	enemyplayer.x = (App->player->position.x + 5) - position.x;
	enemyplayer.y = abs(position.y + 25) - abs(App->player->position.y + 10);

	module = sqrt((pow(enemyplayer.x, 2) + pow(enemyplayer.y, 2)));
	enemyplayeru.x = enemyplayer.x / module;
	enemyplayeru.y = enemyplayer.y / module;

	//angle = atan(enemyplayer.x / enemyplayer.y); do not use. Only if needed

	App->particlesenemies->bala.speed.x = enemyplayeru.x;
	App->particlesenemies->bala.speed.y = enemyplayeru.y;

	App->particlesenemies->bala.position.x = (position.x + App->particlesenemies->bala.speed.x);
	App->particlesenemies->bala.position.y = ((position.y + 25) + App->particlesenemies->bala.speed.y);

	space = 0;
	}

	rand1 = rand() % 300;
	//end_of_shot
	*/
}

void Enemy_Soldier::OnCollision(Collider* collider, Collider* c2) {
	/*if (dieB == false) {
		if (c2->type == COLLIDER_PLAYER_SHOT)
			App->UI->score += 75;
		else if (c2->type == COLLIDER_END_OF_GRENADE)
			App->UI->score += 150;
	}
	dieB = true;*/
	App->particles->AddParticle(App->particles->dieEnemie, collider->rect.x, collider->rect.y, COLLIDER_END_OF_GRENADE, NULL);
}
