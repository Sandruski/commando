#include "Application.h"
#include "SoldierPrisoner.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleUI.h"
#include "ModuleEnemies.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleParticles.h"

Enemy_SoldierPrisoner::Enemy_SoldierPrisoner(int x, int y) : Enemy(x, y)
{
	//ANIMATION MOVE (normal SOLDIER)
	//following spritesheet order (left-to-right)
	movepoints.PushBack({ 6, 195, 16, 22 });
	movepoints.PushBack({ 24, 195, 16, 22 });
	movepoints.PushBack({ 42, 195, 15, 22 });

	movepoints.speed = 0.1f;

	animation = &movepoints;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_SoldierPrisoner::Move()
{
	if ((position.y >= 1481 - 2656) && (App->player->position.y <= 1712 - 2656))
		position.y--;
	else if (position.y == 1480 - 2656) {
		animation = nullptr;
		collider->to_delete = true;
	}
}

void Enemy_SoldierPrisoner::OnCollision(Collider* c1, Collider* c2) {

	/*if (dieB == false) {
		if (c2->type == COLLIDER_PLAYER_SHOT)
			App->UI->score += 75;
		else if (c2->type == COLLIDER_END_OF_GRENADE)
			App->UI->score += 150;
	}
	dieB = true;
	App->enemies->dieE++;*/

	App->particles->AddParticle(App->particles->dieEnemie, c1->rect.x, c1->rect.y, COLLIDER_END_OF_GRENADE, NULL);
	App->enemies->dieE++;
}

