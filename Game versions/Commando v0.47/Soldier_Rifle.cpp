#include "Application.h"
#include "Soldier_Rifle.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModulePlayer.h"
#include "ModuleParticlesEnemies.h"
#include <stdlib.h>
#include <time.h>

#include "SDL/include/SDL_timer.h"

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

	die.PushBack({ 6, 111, 16, 27 });
	die.PushBack({ 40, 104, 15, 27 });
	die.PushBack({ 25, 111, 16, 27 });
	die.PushBack({ 40, 104, 15, 27 });


	animation = &center;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void Enemy_SoldierRifle::Move()
{
	currentTime = SDL_GetTicks();
	currentTime -= lastTime;

	if (dieB == false) {
		lastTime = SDL_GetTicks();
		
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

			//App->particlesenemies->bala.position.x = (position.x + App->particlesenemies->bala.speed.x);
			//App->particlesenemies->bala.position.y = ((position.y + 25) + App->particlesenemies->bala.speed.y);

			space = 0;
		}

		rand1 = rand() % 500;

		//Change of behaviour. Soldier walks backwards
		/*
		if (App->player->position.y <= position.y - 24) {

		}
		*/
	}

	if (dieB == true) {

		animation = &die;
		die.speed = 0.1f;
		if (currentTime > 1000)
			animation = nullptr;
	}
}

void Enemy_SoldierRifle::OnCollision(Collider* c1, Collider* c2) {
	if (dieB == false) {
		if (c2->type == COLLIDER_PLAYER_SHOT)
			App->UI->score += 75;
		else if (c2->type == COLLIDER_END_OF_GRENADE)
			App->UI->score += 150;
	}
	dieB = true;


}