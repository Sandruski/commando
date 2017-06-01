#include "Application.h"
#include "SoldierPath3.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "Path.h"
#include "ModuleEnemies.h"
#include <stdlib.h>
#include <time.h>
#include "ModuleParticlesEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

Enemy_Soldier3::Enemy_Soldier3(int x, int y) : Enemy(x, y)
{
	//ANIMATION MOVE (normal SOLDIER)
	//first sprite of an animation: soldier standing
	//second sprite of an animation: soldier walking

	up.PushBack({ 114, 82, 11, 21 });
	up.PushBack({ 128, 82, 11, 22 });

	down.PushBack({ 80, 82, 13, 23 });
	down.PushBack({ 228, 45, 13, 23 });

	left.PushBack({ 210, 82, 16, 22 });
	left.PushBack({ 228, 82, 16, 22 });

	right.PushBack({ 61, 82, 16, 22 });
	right.PushBack({ 42, 82, 16, 22 });

	up_left.PushBack({ 194, 82, 14, 22 });
	up_left.PushBack({ 6, 82, 16, 22 });

	up_right.PushBack({ 25, 82, 14, 22 });
	up_right.PushBack({ 175, 82, 16, 22 });

	down_left.PushBack({ 96, 82, 15, 22 });
	down_left.PushBack({ 210, 46, 15, 22 });

	down_right.PushBack({ 141, 82, 15, 22 });
	down_right.PushBack({ 158, 82, 15, 22 });

	die.PushBack({ 6, 111, 16, 27 });
	die.PushBack({ 40, 104, 15, 27 });
	die.PushBack({ 25, 111, 16, 27 });
	die.PushBack({ 40, 104, 15, 27 });

	die.speed = 0.1f;
	up.speed = 0.1f;
	down.speed = 0.1f;
	left.speed = 0.1f;
	right.speed = 0.1f;
	up_left.speed = 0.1f;
	up_right.speed = 0.1f;
	down_left.speed = 0.1f;
	down_right.speed = 0.1f;

	//PATHS
	//Path 1
	path1.PushBack({ +0.0f, +0.6f }, 90 - 10);
	path1.PushBack({ -0.6f, +0.6f }, 30 - 10);
	path1.PushBack({ -0.6f, +0.0f }, 50 - 10);

	path1.PushBack({ +0.0f, +0.6f }, 10 - 10);
	path1.PushBack({ -0.6f, +0.0f }, 70 - 10);
	path1.PushBack({ -0.6f, +0.6f }, 80 - 10);
	path1.PushBack({ -0.6f, +0.0f }, 200 - 10);

	//Path 2
	path2.PushBack({ +0.0f, +0.6f }, 100 - 10);
	path2.PushBack({ +0.6f, +0.0f }, 80 - 10);
	path2.PushBack({ +0.0f, -0.6f }, 30 - 10);
	path2.PushBack({ +0.6f, +0.0f }, 90 - 10);

	path2.PushBack({ +0.0f, +0.6f }, 50 - 10);
	path2.PushBack({ -0.6f, +0.0f }, 30 - 10);
	path2.PushBack({ +0.0f, +0.6f }, 20 - 10);
	path2.PushBack({ +0.6f, +0.0f }, 200 - 10);

	//Path 3
	path3.PushBack({ +0.0f, +0.6f }, 90 - 10);
	path3.PushBack({ -0.6f, +0.6f }, 40 - 10);
	path3.PushBack({ +0.0f, +0.6f }, 50 - 10);

	path3.PushBack({ +0.6f, +0.0f }, 40 - 10);
	path3.PushBack({ +0.6f, +0.6f }, 70 - 10);
	path3.PushBack({ +0.0f, +0.6f }, 20 - 10);
	path3.PushBack({ -0.6f, +0.0f }, 100 - 10);

	path3.PushBack({ +0.0f, +0.6f }, 10 - 10);
	path3.PushBack({ -0.6f, +0.0f }, 40 - 10);
	path3.PushBack({ +0.0f, +0.6f }, 50 - 10);
	path3.PushBack({ -0.6f, +0.6f }, 70 - 10);

	path3.PushBack({ +0.0f, +0.6f }, 30 - 10);
	path3.PushBack({ +0.6f, +0.6f }, 40 - 10);
	path3.PushBack({ +0.6f, +0.0f }, 60 - 10);
	path3.PushBack({ +0.0f, +0.6f }, 50 - 10);

	path3.PushBack({ +0.6f, +0.0f }, 200 - 10);

	//Path 4
	path4.PushBack({ +0.0f, +0.6f }, 100 - 10);
	path4.PushBack({ -0.6f, +0.0f }, 20 - 10);
	path4.PushBack({ +0.0f, +0.6f }, 30 - 10);
	path4.PushBack({ +0.6f, +0.0f }, 40 - 10);

	path4.PushBack({ +0.6f, +0.6f }, 20 - 10);
	path4.PushBack({ -0.6f, +0.6f }, 50 - 10);
	path4.PushBack({ -0.6f, +0.0f }, 30 - 10);
	path4.PushBack({ +0.0f, -0.6f }, 20 - 10);

	path4.PushBack({ -0.6f, +0.0f }, 30 - 10);
	path4.PushBack({ +0.0f, +0.6f }, 50 - 10);
	path4.PushBack({ +0.6f, +0.0f }, 60 - 10);
	path4.PushBack({ +0.0f, +0.6f }, 20 - 10);

	path4.PushBack({ +0.6f, +0.0f }, 50 - 10);
	path4.PushBack({ +0.6f, +0.6f }, 30 - 10);
	path4.PushBack({ +0.0f, +0.6f }, 20 - 10);
	path4.PushBack({ +0.6f, +0.0f }, 10 - 10);
	path4.PushBack({ +0.0f, +0.6f }, 20 - 10);

	path4.PushBack({ -0.6f, +0.6f }, 40 - 10);
	path4.PushBack({ -0.6f, +0.0f }, 100 - 10);

	//Path 5
	path5.PushBack({ +0.0f, +0.6f }, 100 - 10);
	path5.PushBack({ +0.6f, +0.6f }, 30 - 10);
	path5.PushBack({ -0.6f, +0.6f }, 80 - 10);
	path5.PushBack({ +0.0f, +0.6f }, 30 - 10);

	path5.PushBack({ +0.6f, +0.0f }, 60 - 10);
	path5.PushBack({ +0.0f, +0.6f }, 20 - 10);
	path5.PushBack({ +0.6f, +0.0f }, 80 - 10);
	path5.PushBack({ +0.6f, +0.6f }, 30 - 10);

	path5.PushBack({ -0.6f, +0.0f }, 170 - 10);
	path5.PushBack({ +0.0f, +0.6f }, 40 - 10);
	path5.PushBack({ +0.6f, +0.0f }, 60 - 10);
	path5.PushBack({ +0.0f, +0.6f }, 50 - 10);

	path5.PushBack({ -0.6f, +0.0f }, 30 - 10);
	path5.PushBack({ +0.0f, +0.6f }, 20 - 10);
	path5.PushBack({ +0.6f, +0.0f }, 30 - 10);
	path5.PushBack({ +0.0f, +0.6f }, 40 - 10);

	path5.PushBack({ -0.6f, +0.0f }, 50 - 10);
	path5.PushBack({ +0.0f, -0.6f }, 20 - 10);
	path5.PushBack({ -0.6f, +0.0f }, 30 - 10);
	path5.PushBack({ +0.0f, +0.6f }, 20 - 10);

	path5.PushBack({ +0.6f, +0.0f }, 30 - 10);
	path5.PushBack({ +0.0f, +0.6f }, 10 - 10);
	path5.PushBack({ +0.6f, +0.0f }, 70 - 10);
	path5.PushBack({ +0.0f, +0.6f }, 30 - 10);
	path5.PushBack({ +0.6f, +0.0f }, 100 - 10);

	//
	/*
	//Path 1
	path1.PushBack({ +0.0f, +0.5f }, 90);
	path1.PushBack({ -0.5f, +0.5f }, 30);
	path1.PushBack({ -0.5f, +0.0f }, 50);

	path1.PushBack({ +0.0f, +0.5f }, 10);
	path1.PushBack({ -0.5f, +0.0f }, 70);
	path1.PushBack({ -0.5f, +0.5f }, 80);
	path1.PushBack({ -0.5f, +0.0f }, 200);

	//Path 2
	path2.PushBack({ +0.0f, +0.5f }, 100);
	path2.PushBack({ +0.5f, +0.0f }, 80);
	path2.PushBack({ +0.0f, -0.5f }, 30);
	path2.PushBack({ +0.5f, +0.0f }, 90);

	path2.PushBack({ +0.0f, +0.5f }, 50);
	path2.PushBack({ -0.5f, +0.0f }, 30);
	path2.PushBack({ +0.0f, +0.5f }, 20);
	path2.PushBack({ +0.5f, +0.0f }, 200);

	//Path 3
	path3.PushBack({ +0.0f, +0.5f }, 90);
	path3.PushBack({ -0.5f, +0.5f }, 40);
	path3.PushBack({ +0.0f, +0.5f }, 50);

	path3.PushBack({ +0.5f, +0.0f }, 40);
	path3.PushBack({ +0.5f, +0.5f }, 70);
	path3.PushBack({ +0.0f, +0.5f }, 20);
	path3.PushBack({ -0.5f, +0.0f }, 100);

	path3.PushBack({ +0.0f, +0.5f }, 10);
	path3.PushBack({ -0.5f, +0.0f }, 40);
	path3.PushBack({ +0.0f, +0.5f }, 50);
	path3.PushBack({ -0.5f, +0.5f }, 70);

	path3.PushBack({ +0.0f, +0.5f }, 30);
	path3.PushBack({ +0.5f, +0.5f }, 40);
	path3.PushBack({ +0.5f, +0.0f }, 60);
	path3.PushBack({ +0.0f, +0.5f }, 50);

	path3.PushBack({ +0.5f, +0.0f }, 200);

	//Path 4
	path4.PushBack({ +0.0f, +0.5f }, 100);
	path4.PushBack({ -0.5f, +0.0f }, 20);
	path4.PushBack({ +0.0f, +0.5f }, 30);
	path4.PushBack({ +0.5f, +0.0f }, 40);

	path4.PushBack({ +0.5f, +0.5f }, 20);
	path4.PushBack({ -0.5f, +0.5f }, 50);
	path4.PushBack({ -0.5f, +0.0f }, 30);
	path4.PushBack({ +0.0f, -0.5f }, 10);

	path4.PushBack({ -0.5f, +0.0f }, 30);
	path4.PushBack({ +0.0f, +0.5f }, 50);
	path4.PushBack({ +0.5f, +0.0f }, 60);
	path4.PushBack({ +0.0f, +0.5f }, 20);

	path4.PushBack({ +0.5f, +0.0f }, 50);
	path4.PushBack({ +0.5f, +0.5f }, 30);
	path4.PushBack({ +0.0f, +0.5f }, 20);
	path4.PushBack({ +0.5f, +0.0f }, 10);
	path4.PushBack({ +0.0f, +0.5f }, 20);

	path4.PushBack({ -0.5f, +0.5f }, 40);
	path4.PushBack({ -0.5f, +0.0f }, 100);

	//Path 5
	path5.PushBack({ +0.0f, +0.5f }, 100);
	path5.PushBack({ +0.5f, +0.5f }, 30);
	path5.PushBack({ -0.5f, +0.5f }, 80);
	path5.PushBack({ +0.0f, +0.5f }, 30);

	path5.PushBack({ +0.5f, +0.0f }, 60);
	path5.PushBack({ +0.0f, +0.5f }, 20);
	path5.PushBack({ +0.5f, +0.0f }, 80);
	path5.PushBack({ +0.5f, +0.5f }, 30);

	path5.PushBack({ -0.5f, +0.0f }, 170);
	path5.PushBack({ +0.0f, +0.5f }, 40);
	path5.PushBack({ +0.5f, +0.0f }, 60);
	path5.PushBack({ +0.0f, +0.5f }, 50);

	path5.PushBack({ -0.5f, +0.0f }, 30);
	path5.PushBack({ +0.0f, +0.5f }, 20);
	path5.PushBack({ +0.5f, +0.0f }, 30);
	path5.PushBack({ +0.0f, +0.5f }, 40);

	path5.PushBack({ -0.5f, +0.0f }, 50);
	path5.PushBack({ +0.0f, -0.5f }, 20);
	path5.PushBack({ -0.5f, +0.0f }, 30);
	path5.PushBack({ +0.0f, +0.5f }, 20);

	path5.PushBack({ +0.5f, +0.0f }, 30);
	path5.PushBack({ +0.0f, +0.5f }, 10);
	path5.PushBack({ +0.5f, +0.0f }, 70);
	path5.PushBack({ +0.0f, +0.5f }, 30);
	path5.PushBack({ +0.5f, +0.0f }, 100);
	*/

	animation = &up;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_Soldier3::Move()
{
	currentTime = SDL_GetTicks();
	currentTime -= lastTime;

	if (original_pos.y == -10 - 2656) {
		position = original_pos + path1.GetCurrentPositionfl(&animation);
		save_step = path1.GetCurrentPositionf();
	}

	if (original_pos.y == -11 - 2656) {
		position = original_pos + path2.GetCurrentPositionfl(&animation);
		save_step = path2.GetCurrentPositionf();
	}

	if (original_pos.y == -12 - 2656) {
		position = original_pos + path3.GetCurrentPositionfl(&animation);
		save_step = path3.GetCurrentPositionf();
	}

	if (original_pos.y == -13 - 2656) {
		position = original_pos + path4.GetCurrentPositionfl(&animation);
		save_step = path4.GetCurrentPositionf();
	}

	if (original_pos.y == -14 - 2656) {
		position = original_pos + path5.GetCurrentPositionfl(&animation);
		save_step = path5.GetCurrentPositionf();
	}

	//ANIMATION CHANGE FOR PATHS

	if ((save_step.x == 0 && save_step.y > 0)) {
		animation = &down;
	}
	else if ((save_step.x == 0 && save_step.y < 0)) {
		animation = &up;
	}
	else if ((save_step.x > 0 && save_step.y == 0)) {
		animation = &right;
	}
	else if ((save_step.x < 0 && save_step.y == 0)) {
		animation = &left;
	}
	else if ((save_step.x > 0 && save_step.y > 0)) {
		animation = &down_right;
	}
	else if ((save_step.x < 0 && save_step.y > 0)) {
		animation = &down_left;
	}
	else if ((save_step.x > 0 && save_step.y < 0)) {
		animation = &up_right;
	}
	else if ((save_step.x < 0 && save_step.y < 0)) {
		animation = &up_left;
	}
	//

	//SHOT
	rand1 = rand() % 300;
	num_shots = rand() % 4;

	if (rand1 == 3 && position.x > 0 && position.x < SCREEN_WIDTH) {

		enemyplayer.x = (App->player->position.x + 5) - position.x;
		enemyplayer.y = fabs(position.y + 25) - fabs(App->player->position.y + 10);

		module = sqrt((pow(enemyplayer.x, 2) + pow(enemyplayer.y, 2)));
		enemyplayeru.x = enemyplayer.x / module;
		enemyplayeru.y = enemyplayer.y / module;

		App->particlesenemies->bala.speed.x = enemyplayeru.x;
		App->particlesenemies->bala.speed.y = enemyplayeru.y;

		for (int i = 0; i <= num_shots; i++) {
			App->particlesenemies->AddParticle(App->particlesenemies->bala, position.x, (position.y + 25), COLLIDER_ENEMY_SHOT, NULL, enemyplayeru); //position.y+30+space
			space = rand() % 10 + 5;
		}

		space = 0;
	}
	//end_of_shot

	if (dieB == true) {

		animation = &die;
		die.speed = 0.1f;
		if (currentTime > 800)
			Esperanza = false;
	}
}

void Enemy_Soldier3::OnCollision(Collider* c1, Collider* c2) {

	if ((c2->type == COLLIDER_FOLLOW)) {
		hi = true;

	}

	else {

		if (c2->type == COLLIDER_WALL) {
			if ((c1->rect.x + c1->rect.w) - c2->rect.x != 1 && (c2->rect.x + c2->rect.w) - c1->rect.x != 1 && (c2->rect.y + c2->rect.h) - c1->rect.y == 1 && (c1->rect.y + c1->rect.h) - c2->rect.y != 1)

				collW = true;

			if ((c1->rect.x + c1->rect.w) - c2->rect.x != 1 && (c2->rect.x + c2->rect.w) - c1->rect.x == 1 && (c2->rect.y + c2->rect.h) - c1->rect.y != 1 && (c1->rect.y + c1->rect.h) - c2->rect.y != 1)

				collA = true;

			if ((c1->rect.x + c1->rect.w) - c2->rect.x != 1 && (c2->rect.x + c2->rect.w) - c1->rect.x != 1 && (c2->rect.y + c2->rect.h) - c1->rect.y != 1 && (c1->rect.y + c1->rect.h) - c2->rect.y == 1)

				collS = true;

			if ((c1->rect.x + c1->rect.w) - c2->rect.x == 1 && (c2->rect.x + c2->rect.w) - c1->rect.x != 1 && (c2->rect.y + c2->rect.h) - c1->rect.y != 1 && (c1->rect.y + c1->rect.h) - c2->rect.y != 1)

				collD = true;

			dont_move = false;
		}


		else {

			hi = false;
			App->particles->AddParticle(App->particles->dieEnemie, collider->rect.x, collider->rect.y, COLLIDER_ENEMYDIE, NULL);
		}
	}
}