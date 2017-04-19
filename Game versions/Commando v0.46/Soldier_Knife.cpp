#include "Application.h"
#include "Soldier_Knife.h"
#include "ModuleCollision.h"

Enemy_SoldierKnife::Enemy_SoldierKnife(int x, int y) : Enemy(x, y)
{
	//ANIMATION TURN (SOLDIER WITH RIFLE)
	//moving to the left
	turn.PushBack({ 107, 110, 18, 18 }); //center
	turn.PushBack({ 142, 110, 18, 18 }); //more left
	turn.PushBack({ 159, 110, 18, 18 }); //MORE left

										 //moving to the right
	turn.PushBack({ 107, 110, 18, 18 }); //center
	turn.PushBack({ 125, 110, 18, 18 }); //more right
	turn.PushBack({ 177, 110, 18, 18 }); //MORE right

	turn.speed = 0.1f;

	animation = &turn;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_SoldierKnife::Move()
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
