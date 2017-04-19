#include "Application.h"
#include "Prisoner.h"
#include "ModuleCollision.h"

Enemy_Prisoner::Enemy_Prisoner(int x, int y) : Enemy(x, y)
{
	//ANIMATION ANIMATED (PRISONER)
	animated.PushBack({ 61, 195, 15, 22 });
	animated.PushBack({ 79, 195, 15, 22 });
	animated.PushBack({ 96, 195, 15, 22 });

	//ANIMATION STAND (PRISONER)
	stand.PushBack({ 151, 195, 16, 22 });
	stand.PushBack({ 169, 195, 16, 22 });

	//ANIMATION RUN (PRISONER)
	run.PushBack({ 114, 195, 16, 32 });
	run.PushBack({ 133, 195, 16, 31 });

	animated.speed = 0.1f;
	stand.speed = 0.1f;
	run.speed = 0.1f;

	animation = &stand;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_PRISONER, (Module*)App->enemies);
}

void Enemy_Prisoner::Move()
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
