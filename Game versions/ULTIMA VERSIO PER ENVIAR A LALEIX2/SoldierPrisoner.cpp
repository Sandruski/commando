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

	die.PushBack({ 6, 111, 16, 27 });
	die.PushBack({ 40, 104, 15, 27 });
	die.PushBack({ 25, 111, 16, 27 });
	die.PushBack({ 40, 104, 15, 27 });

	animation = &movepoints;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_SoldierPrisoner::Move()
{
	currentTime = SDL_GetTicks();
	currentTime -= lastTime;

	if (dieB == false) {
		lastTime = SDL_GetTicks();
		if ((position.y >= 1481 - 2656) && (App->player->position.y <= 1712 - 2656))
			position.y--;
		else if (position.y == 1480 - 2656) {
			animation = nullptr;
			collider->to_delete = true;
		}

	}
	else {
		animation = &die;
		die.speed = 0.1f;
		if (currentTime > 800) {
			Esperanza = false;
			App->enemies->dieE++;
		}
	}
}

void Enemy_SoldierPrisoner::OnCollision(Collider* c1, Collider* c2) {

	App->particles->AddParticle(App->particles->dieEnemie, c1->rect.x, c1->rect.y, COLLIDER_END_OF_GRENADE, NULL);


}

