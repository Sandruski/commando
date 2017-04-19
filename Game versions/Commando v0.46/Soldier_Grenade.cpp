#include "Application.h"
#include "Soldier_Grenade.h"
#include "ModuleCollision.h"

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
