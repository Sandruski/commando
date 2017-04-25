#include "Application.h"
#include "Soldier_Grenade.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModulePlayer.h"
#include "ModuleParticlesEnemies.h"
#include "ModuleParticles.h"
#include <stdlib.h>
#include <time.h>

#include "SDL/include/SDL_timer.h"

Enemy_SoldierGrenade::Enemy_SoldierGrenade(int x, int y) : Enemy(x, y)
{
	//ANIMATION TURN (SOLDIER WHO THROWS GRENADES)

	turn.PushBack({ 56, 110, 16, 22 }); //normal
	turn.PushBack({ 74, 110, 16, 22 }); //down
	turn.PushBack({ 91, 110, 16, 22 }); //MORE down

	turn.speed = 0.1f;



	animation = &turn;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_SoldierGrenade::Move()
{
	//SHOT
	num_shots = rand() % 4;

	if (rand1 == 3 && App->player->position.y > position.y + 24) {

		for (int i = 0; i <= num_shots; i++) {
			App->particlesenemies->AddParticle(App->particlesenemies->grenade, position.x, (position.y + 25), COLLIDER_PLAYER_GRENADE, NULL, enemyplayeru); //position.y+30+space
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


}

void Enemy_SoldierGrenade::OnCollision(Collider* c1, Collider* c2) {
	/*if (dieB == false) {
		if (c2->type == COLLIDER_PLAYER_SHOT)
			App->UI->score += 75;
		else if (c2->type == COLLIDER_END_OF_GRENADE)
			App->UI->score += 150;
	}
	dieB = true;*/
	App->particles->AddParticle(App->particles->dieEnemie, c1->rect.x, c1->rect.y, COLLIDER_END_OF_GRENADE, NULL);


}