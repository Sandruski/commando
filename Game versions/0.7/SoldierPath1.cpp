#include "Application.h"
#include "SoldierPath1.h"
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

Enemy_Soldier1::Enemy_Soldier1(int x, int y) : Enemy(x, y)
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
	//fPoint speed, uint frames, Animation* animation = nullptr
	pathA.PushBack({ +0.5f, +0.0f }, 140);
	pathA.PushBack({ -0.5f, +0.5f }, 40);
	pathA.PushBack({ +0.0f, +0.5f }, 10);
	pathA.PushBack({ +0.5f, +0.0f }, 60);
	pathA.PushBack({ +0.0f, +0.5f }, 110);
	pathA.PushBack({ +0.5f, +0.0f }, 70);
	pathA.PushBack({ +0.0f, +0.5f }, 30);
	pathA.PushBack({ -0.5f, +0.0f }, 90);

	pathB.PushBack({ -0.5f, +0.0f }, 110);
	pathB.PushBack({ +0.0f, +0.5f }, 40);
	pathB.PushBack({ +0.5f, +0.0f }, 40);
	pathB.PushBack({ +0.0f, +0.5f }, 50);
	pathB.PushBack({ -0.5f, +0.0f }, 60);
	pathB.PushBack({ +0.5f, +0.5f }, 30);
	pathB.PushBack({ +0.5f, +0.0f }, 30);

	animation = &up;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_Soldier1::Move()
{
	currentTime = SDL_GetTicks();
	currentTime -= lastTime;

	if (dont_move && !NO1) {
		if (hi) {
			one = false;

			anim1 = false;
			anim2 = true;

			if (App->player->position.y >= 0) {
				enemyplayer2.x = App->player->position.x - position.x;
				enemyplayer2.y = -fabs(position.y) + (App->player->position.y);
			}
			else {
				enemyplayer2.x = App->player->position.x - position.x;
				enemyplayer2.y = fabs(position.y) - fabs(App->player->position.y);
			}

			module = sqrt((pow(enemyplayer2.x, 2) + pow(enemyplayer2.y, 2)));

			enemyplayeru2.x = enemyplayer2.x / module;
			enemyplayeru2.y = enemyplayer2.y / module;

			position.x += enemyplayeru2.x / 1.5;
			position.y += enemyplayeru2.y / 1.5;

			another.x = position.x;
			another.y = position.y;

			yeah = true;

		}
		else {
			anim2 = false;
			anim1 = true;

			//DIFFERENT PATHS GO HERE

			//Path A (left-right)
			if (original_pos.x < SCREEN_WIDTH / 2) {
				if (one) {
					position = original_pos + pathA.GetCurrentPositionfl(&animation);
					save_step = pathA.GetCurrentPositionf(); //it returns an fPoint of the speed of the current step
				}
				else if (!one && two) {

					if (yeah) {
						pathA.accumulated_speed = { 0.0f, 0.0f };
						pathA.current_frame = 0;
					}

					position = another + pathA.GetCurrentPositionfl(&animation);
					save_step = pathA.GetCurrentPositionf(); //it returns an fPoint of the speed of the current step
					yeah = false;
				}
			}


			//Path B (right-left)
			if (original_pos.x > SCREEN_WIDTH / 2) {
				if (one) {
					position = original_pos + pathB.GetCurrentPositionfl(&animation);
					save_step = pathB.GetCurrentPositionf(); //it returns an fPoint of the speed of the current step
				}
				else if (!one && two) {

					if (yeah) {
						pathB.accumulated_speed = { 0.0f, 0.0f };
						pathB.current_frame = 0;
					}

					position = another + pathB.GetCurrentPositionfl(&animation);
					save_step = pathB.GetCurrentPositionf(); //it returns an fPoint of the speed of the current step
					yeah = false;
				}
			}
			//end_of_different_paths

		}
	}
	else {
		if (hi && !NO1) {
			one = false;

			anim1 = false;
			anim2 = true;

			if (App->player->position.y >= 0) {
				enemyplayer2.x = App->player->position.x - position.x;
				enemyplayer2.y = -fabs(position.y) + (App->player->position.y);
			}
			else {
				enemyplayer2.x = App->player->position.x - position.x;
				enemyplayer2.y = fabs(position.y) - fabs(App->player->position.y);
			}

			module = sqrt((pow(enemyplayer2.x, 2) + pow(enemyplayer2.y, 2)));

			enemyplayeru2.x = enemyplayer2.x / module;
			enemyplayeru2.y = enemyplayer2.y / module;

			position.x += enemyplayeru2.x / 1.5;
			position.y += enemyplayeru2.y / 1.5;

			another.x = position.x;
			another.y = position.y;

			yeah = true;
		}
	}


	if (collW) {
		NO1 = true;
		position.y++;
	}
	else if (collA) {
		NO1 = true;
		position.x++;
	}
	else if (collS) {
		NO1 = true;
		position.y--;
	}
	else if (collD) {
		NO1 = true;
		position.x--;
	}

	//ANIMATION CHANGE FOR PATHS
	if (anim1) {
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
	}
	//

	//ANIMATION CHANGE FOR FOLLOW
	if (anim2) {
		if ((enemyplayeru2.x == 0 && enemyplayeru.y > 0)) {
			animation = &down;
		}
		else if ((enemyplayeru2.x == 0 && enemyplayeru.y < 0)) {
			animation = &up;
		}
		else if ((enemyplayeru2.x > 0 && enemyplayeru.y == 0)) {
			animation = &right;
		}
		else if ((enemyplayeru2.x < 0 && enemyplayeru.y == 0)) {
			animation = &left;
		}
		else if ((enemyplayeru2.x > 0 && enemyplayeru.y > 0)) {
			animation = &down_right;
		}
		else if ((enemyplayeru2.x < 0 && enemyplayeru.y > 0)) {
			animation = &down_left;
		}
		else if ((enemyplayeru2.x > 0 && enemyplayeru.y < 0)) {
			animation = &up_right;
		}
		else if ((enemyplayeru2.x < 0 && enemyplayeru.y < 0)) {
			animation = &up_left;
		}
	}
	//

	//SHOT
	rand1 = rand() % 300;
	num_shots = rand() % 4;

	if (rand1 == 3 && position.x > 0 && position.x < SCREEN_WIDTH) {

		enemyplayer.x = (App->player->position.x + 5) - position.x;
		enemyplayer.y = -fabs(position.y + 25) + fabs(App->player->position.y + 10);

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

	hi = false;

	dont_move = true;

	collW = false;
	collA = false;
	collS = false;
	collD = false;

	NO1 = false;
}

void Enemy_Soldier1::OnCollision(Collider* c1, Collider* c2) {

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
