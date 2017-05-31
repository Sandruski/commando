#include "Application.h"
#include "SoldierPath2.h"
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

Enemy_Soldier2::Enemy_Soldier2(int x, int y) : Enemy(x, y)
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

	//Path A
	//start of each path A
	pathA.PushBack({ -0.5f, +0.0f }, 70);
	pathA.PushBack({ -0.5f, -0.5f }, 30);
	pathA.PushBack({ -0.5f, +0.5f }, 60);
	pathA.PushBack({ -0.5f, +0.0f }, 30);
	//
	pathA.PushBack({ +0.0f, +0.5f }, 30);
	pathA.PushBack({ -0.5f, +0.0f }, 40);
	pathA.PushBack({ +0.0f, +0.5f }, 80);
	pathA.PushBack({ -0.5f, +0.0f }, 70);
	pathA.PushBack({ +0.0f, +0.5f }, 50);
	pathA.PushBack({ -0.5f, +0.0f }, 100);
	//

	//Path A1
	pathA1.PushBack({ -0.5f, +0.0f }, 70);
	pathA1.PushBack({ -0.5f, -0.5f }, 30);
	pathA1.PushBack({ -0.5f, +0.5f }, 60);
	pathA1.PushBack({ -0.5f, +0.0f }, 30);
	//
	pathA1.PushBack({ +0.0f, +0.5f }, 30);
	pathA1.PushBack({ -0.5f, +0.0f }, 80);
	pathA1.PushBack({ +0.0f, -0.5f }, 50);
	pathA1.PushBack({ -0.5f, +0.0f }, 80);
	pathA1.PushBack({ +0.0f, +0.5f }, 50);
	pathA1.PushBack({ -0.5f, +0.0f }, 100);

	//Path B
	//start of each path B
	pathB.PushBack({ +0.5f, +0.0f }, 60);
	pathB.PushBack({ +0.5f, -0.5f }, 30);
	pathB.PushBack({ +0.5f, +0.5f }, 60);
	pathB.PushBack({ +0.5f, +0.0f }, 30);
	//
	pathB.PushBack({ +0.5f, +0.0f }, 70);
	pathB.PushBack({ +0.0f, -0.5f }, 50);
	pathB.PushBack({ +0.5f, +0.0f }, 90);
	pathB.PushBack({ +0.0f, +0.5f }, 30);
	pathB.PushBack({ +0.5f, +0.0f }, 200);
	//

	//Path B1
	pathB1.PushBack({ +0.5f, +0.0f }, 60);
	pathB1.PushBack({ +0.5f, -0.5f }, 30);
	pathB1.PushBack({ +0.5f, +0.5f }, 60);
	pathB1.PushBack({ +0.5f, +0.0f }, 30);
	//
	pathB1.PushBack({ +0.5f, +0.0f }, 10);
	pathB1.PushBack({ +0.0f, +0.5f }, 30);
	pathB1.PushBack({ -0.5f, +0.0f }, 60);
	pathB1.PushBack({ +0.0f, +0.5f }, 60);
	pathB1.PushBack({ -0.5f, +0.0f }, 600);
	//

	//Path C
	//start of each path C
	pathC.PushBack({ +0.5f, +0.0f }, 90);
	pathC.PushBack({ +0.5f, -0.5f }, 30);
	pathC.PushBack({ +0.5f, +0.5f }, 60);
	pathC.PushBack({ +0.5f, +0.0f }, 30);
	//
	pathC.PushBack({ +0.5f, +0.0f }, 60);
	pathC.PushBack({ +0.0f, +0.5f }, 40);
	pathC.PushBack({ +0.5f, +0.0f }, 70);
	pathC.PushBack({ +0.0f, +0.5f }, 100);
	pathC.PushBack({ +0.5f, +0.0f }, 40);
	pathC.PushBack({ +0.0f, +0.5f }, 700);
	//

	//Path C1
	pathC1.PushBack({ +0.5f, +0.0f }, 90);
	pathC1.PushBack({ +0.5f, -0.5f }, 30);
	pathC1.PushBack({ +0.5f, +0.5f }, 60);
	pathC1.PushBack({ +0.5f, +0.0f }, 30);
	//
	pathC1.PushBack({ +0.5f, +0.0f }, 10);
	pathC1.PushBack({ +0.0f, +0.5f }, 70);
	pathC1.PushBack({ +0.5f, +0.0f }, 50);
	pathC1.PushBack({ +0.0f, +0.5f }, 40);
	pathC1.PushBack({ -0.5f, +0.0f }, 200);
	pathC1.PushBack({ +0.0f, +0.5f }, 70);
	pathC1.PushBack({ -0.5f, +0.0f }, 80);
	pathC1.PushBack({ +0.0f, -0.5f }, 90);
	pathC1.PushBack({ -0.5f, +0.0f }, 70);
	pathC1.PushBack({ +0.0f, +0.5f }, 20);
	pathC1.PushBack({ -0.5f, +0.0f }, 300);
	//

	//Path D
	//start of each path D
	pathD.PushBack({ -0.5f, +0.0f }, 70);
	pathD.PushBack({ -0.5f, -0.5f }, 30);
	pathD.PushBack({ -0.5f, +0.5f }, 60);
	pathD.PushBack({ -0.5f, +0.0f }, 30);
	//
	pathD.PushBack({ -0.5f, +0.0f }, 30);
	pathD.PushBack({ +0.0f, -0.5f }, 50);
	pathD.PushBack({ -0.5f, +0.0f }, 60);
	pathD.PushBack({ +0.0f, +0.5f }, 20);
	pathD.PushBack({ -0.5f, +0.0f }, 50);
	pathD.PushBack({ +0.0f, +0.5f }, 40);
	pathD.PushBack({ -0.5f, +0.0f }, 60);
	pathD.PushBack({ +0.0f, +0.5f }, 50);
	pathD.PushBack({ -0.5f, +0.0f }, 300);
	//

	//Path D1
	pathD1.PushBack({ -0.5f, +0.0f }, 70);
	pathD1.PushBack({ -0.5f, -0.5f }, 30);
	pathD1.PushBack({ -0.5f, +0.5f }, 60);
	pathD1.PushBack({ -0.5f, +0.0f }, 30);
	//
	pathD1.PushBack({ -0.5f, +0.0f }, 80);
	pathD1.PushBack({ +0.0f, +0.5f }, 30);
	pathD1.PushBack({ -0.5f, +0.0f }, 50);
	pathD1.PushBack({ -0.5f, +0.0f }, 80);
	pathD1.PushBack({ +0.0f, +0.5f }, 60);
	pathD1.PushBack({ +0.5f, +0.0f }, 90);
	pathD1.PushBack({ +0.0f, +0.5f }, 40);
	pathD1.PushBack({ +0.5f, +0.0f }, 200);
	pathD1.PushBack({ +0.0f, +0.5f }, 50);
	pathD1.PushBack({ +0.5f, +0.0f }, 400);

	animation = &up;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_Soldier2::Move()
{
	currentTime = SDL_GetTicks();
	currentTime -= lastTime;

	if (original_pos.y == 2498 - 2656) {
		position = original_pos + pathA.GetCurrentPositionfl(&animation);
		save_step = pathA.GetCurrentPositionf();
	}

	if (original_pos.y == 2499 - 2656) {
		position = original_pos + pathA1.GetCurrentPositionfl(&animation);
		save_step = pathA1.GetCurrentPositionf();
	}

	if (original_pos.y == 2272 - 2656) {
		position = original_pos + pathB.GetCurrentPositionfl(&animation);
		save_step = pathB.GetCurrentPositionf();
	}

	if (original_pos.y == 2271 - 2656) {
		position = original_pos + pathB1.GetCurrentPositionfl(&animation);
		save_step = pathB1.GetCurrentPositionf();
	}

	if (original_pos.y == 2000 - 2656) {
		position = original_pos + pathC.GetCurrentPositionfl(&animation);
		save_step = pathC.GetCurrentPositionf();
	}

	if (original_pos.y == 2001 - 2656) {
		position = original_pos + pathC1.GetCurrentPositionfl(&animation);
		save_step = pathC1.GetCurrentPositionf();
	}

	if (original_pos.y == 1755 - 2656) {
		position = original_pos + pathD.GetCurrentPositionfl(&animation);
		save_step = pathD.GetCurrentPositionf();
	}

	if (original_pos.y == 1754 - 2656) {
		position = original_pos + pathD1.GetCurrentPositionfl(&animation);
		save_step = pathD1.GetCurrentPositionf();
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
		animation = &right; //down-right
	}
	else if ((save_step.x < 0 && save_step.y > 0)) {
		animation = &left; //down-left
	}
	else if ((save_step.x > 0 && save_step.y < 0)) {
		animation = &right; //up-right
	}
	else if ((save_step.x < 0 && save_step.y < 0)) {
		animation = &left; //up-left
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

void Enemy_Soldier2::OnCollision(Collider* c1, Collider* c2) {

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
			App->particles->AddParticle(App->particles->dieEnemie, collider->rect.x, collider->rect.y, COLLIDER_END_OF_GRENADE, NULL);
		}
	}
}
