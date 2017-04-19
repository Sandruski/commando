#include "Application.h"
#include "Crazy_Green.h"
#include "ModuleCollision.h"

Enemy_CrazyGreen::Enemy_CrazyGreen(int x, int y) : Enemy(x, y)
{
	//ANIMATION RUN (CRAZY GREEN SOLDIER)
	run.PushBack({ 112, 147, 15, 23 });
	run.PushBack({ 131, 147, 19, 22 });

	//ANIMATION OF CRAZY GREEN SOLDIER DYING (green soldier)
	die.PushBack({ 152, 150, 16, 24 });
	die.PushBack({ 170, 150, 16, 24 });
	die.PushBack({ 207, 147, 10, 8 }); //skull

	run.speed = 0.1f;
	die.speed = 0.1f;

	animation = &run;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_CrazyGreen::Move()
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
