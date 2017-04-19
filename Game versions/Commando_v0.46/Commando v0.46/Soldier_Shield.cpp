#include "Application.h"
#include "Soldier_Shield.h"
#include "ModuleCollision.h"

Enemy_SoldierShield::Enemy_SoldierShield(int x, int y) : Enemy(x, y)
{
	//ANIMATION MOVE (SOLDIER WITH SHIELD)
	move.PushBack({ 6, 147, 15, 20 });
	move.PushBack({ 23, 147, 16, 22 });
	move.PushBack({ 41, 147, 16, 22 });
	move.PushBack({ 59, 147, 14, 17 });

	//ANIMATION SOLDIER SURRENDERING
	surrender.PushBack({ 75, 147, 16, 31 });
	surrender.PushBack({ 95, 147, 13, 32 });

	//this soldier has the same dying animation than normal soldiers (even though it's green)

	move.speed = 0.1f;
	surrender.speed = 0.1f;

	animation = &move;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_SoldierShield::Move()
{
	/*
	if (going_up)
	{
	if (wave > 1.0f)
	going_up = false;
	else
	wave += 0.05f;
	}
	else
	{
	if (wave < -1.0f)
	going_up = true;
	else
	wave -= 0.05f;
	}

	position.y = original_y + (25.0f * sinf(wave));
	position.x -= 1;
	*/
}
