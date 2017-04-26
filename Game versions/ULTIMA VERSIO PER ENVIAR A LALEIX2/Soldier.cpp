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

#include "SDL/include/SDL_timer.h"

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
	path.PushBack({ -0.5f, +0.5f }, 50);
	path.PushBack({ -0.5f, +0.0f }, 20);
	path.PushBack({ -0.5f, -0.5f }, 40);
	path.PushBack({ +0.0f, +0.5f }, 10);
	path.PushBack({ -0.5f, +0.0f }, 50);
	path.PushBack({ +0.0f, +0.5f }, 20);
	path.PushBack({ -0.5f, +0.5f }, 70);

	path1.PushBack({ -0.5f, +0.0f }, 20);
	path1.PushBack({ -0.5f, -0.5f }, 30);
	path1.PushBack({ -0.5f, +0.0f }, 20);
	path1.PushBack({ -0.5f, -0.5f }, 30);
	path1.PushBack({ -0.5f, +0.0f }, 40);
	path1.PushBack({ -0.5f, +0.5f }, 20);
	path1.PushBack({ -0.5f, +0.0f }, 50);

	path2.PushBack({ +0.5f, +0.0f }, 60);
	path2.PushBack({ +0.5f, -0.5f }, 10);
	path2.PushBack({ +0.5f, +0.0f }, 20);
	path2.PushBack({ +0.5f, -0.5f }, 30);
	path2.PushBack({ +0.5f, +0.0f }, 90);

	path3.PushBack({ +0.5f, +0.0f }, 50);
	path3.PushBack({ -0.5f, +0.0f }, 40);
	path3.PushBack({ +0.5f, +0.0f }, 40);
	path3.PushBack({ +0.0f, -0.5f }, 50);
	path3.PushBack({ +0.5f, +0.0f }, 20);

	path_fb.PushBack({ +0.5f, +0.5f }, 20);
	path_fb.PushBack({ +0.0f, +0.5f }, 10);
	path_fb.PushBack({ +0.5f, +0.5f }, 30);
	path_fb.PushBack({ -0.5f, +0.5f }, 30);
	path_fb.PushBack({ -0.5f, +0.0f }, 20);
	path_fb.PushBack({ +0.0f, +0.5f }, 50);
	path_fb.PushBack({ -0.5f, +0.0f }, 10);

	path_fb1.PushBack({ -0.5f, +0.5f }, 20);
	path_fb1.PushBack({ +0.0f, +0.5f }, 10);
	path_fb1.PushBack({ -0.5f, +0.5f }, 30);
	path_fb1.PushBack({ +0.5f, +0.5f }, 30);
	path_fb1.PushBack({ +0.0f, +0.5f }, 40);
	path_fb1.PushBack({ +0.5f, +0.0f }, 10);
	path_fb1.PushBack({ +0.5f, +0.0f }, 20);
	path_fb1.PushBack({ +0.0f, +0.5f }, 30);

	path_fb2.PushBack({ +0.0f, +0.5f }, 30);
	path_fb2.PushBack({ +0.5f, +0.0f }, 10);
	path_fb2.PushBack({ +0.5f, +0.5f }, 10);
	path_fb2.PushBack({ +0.5f, +0.0f }, 10);

	animation = &up;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_Soldier::Move()
{

	currentTime = SDL_GetTicks();
	currentTime -= lastTime;

	if (original_pos.y == 2706 - 2656 || original_pos.y == 2460 - 2656 || original_pos.y == 2408 - 2656 || original_pos.y == 2154 - 2656
		|| original_pos.y == 1693 - 2656 || original_pos.y == 1624 - 2656 || original_pos.y == 1023 - 2656 || original_pos.y == 896 - 2656
		|| original_pos.y == 699 - 2656 || original_pos.y == 688 - 2656 || position.y == 538 - 2656) {
		position = original_pos + path.GetCurrentPosition(&animation);
		save_step = path.GetCurrentPositionf(); //it returns an fPoint of the speed of the current step
	}

	if (original_pos.y == 2763 - 2656 || original_pos.y == 2678 - 2656 || original_pos.y == 2465 - 2656 || original_pos.y == 2332 - 2656
		|| original_pos.y == 1865 - 2656 || original_pos.y == 531 - 2656 || original_pos.y == 283 - 2656) {
		position = original_pos + path1.GetCurrentPosition(&animation);
		save_step = path1.GetCurrentPositionf(); //it returns an fPoint of the speed of the current step
	}

	if (original_pos.y == 2579 - 2656 || original_pos.y == 2245 - 2656 || original_pos.y == 2212 - 2656 || original_pos.y == 1962 - 2656
		|| original_pos.y == 1619 - 2656 || original_pos.y == 621 - 2656) {
		position = original_pos + path2.GetCurrentPosition(&animation);
		save_step = path2.GetCurrentPositionf(); //it returns an fPoint of the speed of the current step
	}

	if (original_pos.y == 2348 - 2656 || original_pos.y == 2230 - 2656 || original_pos.y == 1970 - 2656 || original_pos.y == 1500 - 2656
		|| original_pos.y == 812 - 2656) {
		position = original_pos + path3.GetCurrentPosition(&animation);
		save_step = path3.GetCurrentPositionf(); //it returns an fPoint of the speed of the current step
	}

	if (original_pos.y == 111 - 2656 || original_pos.y == 104 - 2656 || original_pos.y == -2 - 2656 || original_pos.y == -5 - 2656
		|| original_pos.y == -8 - 2656 || original_pos.y == 0 - 2656 || original_pos.y == 120 - 2656) {

		position = original_pos + path_fb.GetCurrentPosition(&animation);
		save_step = path_fb.GetCurrentPositionf(); //it returns an fPoint of the speed of the current step
	}

	if (original_pos.y == 125 - 2656 || original_pos.y == 57 - 2656 || original_pos.y == 98 - 2656 || original_pos.y == 55 - 2656
		|| original_pos.y == 42 - 2656 || original_pos.y == 20 - 2656 || original_pos.y == 30 - 2656) {

		position = original_pos + path_fb1.GetCurrentPosition(&animation);
		save_step = path_fb1.GetCurrentPositionf(); //it returns an fPoint of the speed of the current step
	}

	if (original_pos.y == 35 - 2656 || original_pos.y == 1 - 2656 || original_pos.y == 2 - 2656 || original_pos.y == 7 - 2656
		|| original_pos.y == 4 - 2656) {

		position = original_pos + path_fb2.GetCurrentPosition(&animation);
		save_step = path_fb2.GetCurrentPositionf(); //it returns an fPoint of the speed of the current step
	}


	/*
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
	*/

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

	num_shots = rand() % 4;

	if (rand1 == 3 && position.x > 0 && position.x < SCREEN_WIDTH) {

		for (int i = 0; i <= num_shots; i++) {
			App->particlesenemies->AddParticle(App->particlesenemies->bala, position.x, (position.y + 25), COLLIDER_ENEMY_SHOT, NULL, enemyplayeru); //position.y+30+space
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

	if (dieB == true) {

		animation = &die;
		die.speed = 0.1f;
		if (currentTime > 800)
			Esperanza = false;
	}
}

void Enemy_Soldier::OnCollision(Collider* collider, Collider* c2) {
	
	if (c2->type == COLLIDER_WALL) {

		if ((collider->rect.x + collider->rect.w) - c2->rect.x != 1 && (c2->rect.x + c2->rect.w) - collider->rect.x != 1 && (c2->rect.y + c2->rect.h) - collider->rect.y == 1 && (collider->rect.y + collider->rect.h) - c2->rect.y != 1)

			collW = true;

		if ((collider->rect.x + collider->rect.w) - c2->rect.x != 1 && (c2->rect.x + c2->rect.w) - collider->rect.x == 1 && (c2->rect.y + c2->rect.h) - collider->rect.y != 1 && (collider->rect.y + collider->rect.h) - c2->rect.y != 1)

			collA = true;

		if ((collider->rect.x + collider->rect.w) - c2->rect.x != 1 && (c2->rect.x + c2->rect.w) - collider->rect.x != 1 && (c2->rect.y + c2->rect.h) - collider->rect.y != 1 && (collider->rect.y + collider->rect.h) - c2->rect.y == 1)

			collS = true;

		if ((collider->rect.x + collider->rect.w) - c2->rect.x == 1 && (c2->rect.x + c2->rect.w) - collider->rect.x != 1 && (c2->rect.y + c2->rect.h) - collider->rect.y != 1 && (collider->rect.y + collider->rect.h) - c2->rect.y != 1)

			collD = true;

	}
	if (dieB == false) {
		if (c2->type == COLLIDER_PLAYER_SHOT)
			App->UI->score += 75;
		else if (c2->type == COLLIDER_END_OF_GRENADE)
			App->UI->score += 150;
	}
	dieB = true;
	//App->particles->AddParticle(App->particles->dieEnemie, collider->rect.x, collider->rect.y, COLLIDER_END_OF_GRENADE, NULL);
}
