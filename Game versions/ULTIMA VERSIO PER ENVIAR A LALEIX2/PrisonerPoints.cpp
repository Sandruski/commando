#include "Application.h"
#include "PrisonerPoints.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"

Enemy_PrisonerPoints::Enemy_PrisonerPoints(int x, int y) : Enemy(x, y)
{
	//ANIMATION MOVE (normal SOLDIER)
	//following spritesheet order (left-to-right)
	movepoints.PushBack({ 61, 195, 15, 22 });
	movepoints.PushBack({ 79, 195, 15, 22 });
	movepoints.PushBack({ 96, 195, 15, 22 });

	move2.PushBack({ 114, 195, 16, 32 });
	move2.PushBack({ 133, 195, 16, 31 });

	movepoints.speed = 0.1f;
	move2.speed = 0.1f;

	animation = &movepoints;

	//collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_PrisonerPoints::Move()
{

	if ((position.y >= -1200) && (App->player->position.y <= 1712 - 2656) && bonus == false)
		position.y--;
	if (position.y == -1200)
		Esperanza = false;

	if (App->enemies->dieE == 4) {
		animation = &move2;
		position.x++;
		if (bonus == false)
			App->UI->score += 500;
		bonus = true;
	}
}