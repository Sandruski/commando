#include "Application.h"
#include "Soldier.h"
#include "ModuleCollision.h"

Enemy_Soldier::Enemy_Soldier(int x, int y) : Enemy(x, y)
{
	//ANIMATION MOVE (normal SOLDIER)
	//following spritesheet order (left-to-right)
	move.PushBack({ 6, 82, 16, 22 });
	move.PushBack({ 25, 82, 14, 22 });
	move.PushBack({ 42, 82, 16, 22 });
	move.PushBack({ 61, 82, 16, 22 });
	move.PushBack({ 80, 82, 13, 23 });
	move.PushBack({ 96, 82, 15, 22 });
	move.PushBack({ 114, 82, 11, 21 });
	move.PushBack({ 128, 82, 11, 22 });
	move.PushBack({ 141, 82, 15, 22 });
	move.PushBack({ 158, 82, 15, 22 });
	move.PushBack({ 175, 82, 16, 22 });
	move.PushBack({ 194, 82, 14, 22 });
	move.PushBack({ 210, 82, 16, 22 });
	move.PushBack({ 228, 82, 16, 22 });

	//ANIMATION OF SOLDIER DYING (grey soldier)
	die.PushBack({ 6, 111, 16, 27 });
	die.PushBack({ 25, 111, 16, 27 });
	die.PushBack({ 43, 82, 10, 8 }); //skull

	move.speed = 0.1f;
	die.speed = 0.1f;

	animation = &move;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_Soldier::Move()
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
