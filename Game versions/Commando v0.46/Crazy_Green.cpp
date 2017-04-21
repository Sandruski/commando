#include "Application.h"
#include "Crazy_Green.h"
#include "ModuleCollision.h"

Enemy_CrazyGreen::Enemy_CrazyGreen(int x, int y) : Enemy(x, y)
{
	//ANIMATION RUN (CRAZY GREEN SOLDIER)
	run1.PushBack({ 112, 147, 15, 23 });
	run1.PushBack({ 131, 147, 19, 22 });

	run2.PushBack({ 112, 171, 15, 23 });
	run2.PushBack({ 131, 171, 19, 22 });

	//ANIMATION OF CRAZY GREEN SOLDIER DYING (green soldier)
	die.PushBack({ 152, 150, 16, 24 });
	die.PushBack({ 170, 150, 16, 24 });
	die.PushBack({ 207, 147, 10, 8 }); //skull

	run1.speed = 0.05f;
	run2.speed = 0.05f;
	die.speed = 0.1f;

	animation = &run2;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_CrazyGreen::Move()
{

	if (cont == 0) {
		animation = &run2;
		if (position.x < 190)
			position.x++;
		if (position.y > 58 - 2656)
			position.y--;
		if (position.y == 58 - 2656 && position.x == 190)
			cont++;
	}
	if (cont == 1) {
		animation = &run1;
		if (position.x > 100)
			position.x--;
		if (position.x < 130 && position.x > 101)
			position.y++;
		if (position.x == 100)
			cont++;
	}
	if (cont == 2) {
		if (position.y > 58 - 2656)
			position.y--;
		if (position.x > 80)
			position.x--;
		if (position.x == 80 && position.y == 58 - 2656)
			cont++;
	}
	if (cont == 3) {
		animation = &run2;
		if (position.x < 160)
			position.x++;
		if (position.y > 58 - 2656)
			position.y--;
		if (position.y == 58 - 2656 && position.x == 160)
			cont++;
	}
	if (cont == 4) {
		if (position.x < 190)
			position.x++;
		if (position.y < 88 - 2656)
			position.y++;
		if (position.x == 190 && position.y == 88 - 2656)
			cont++;
	}
	if (cont == 5) {
		animation = &run1;
		if (position.x > 80)
			position.x--;
		if (position.y > 58 - 2656)
			position.y--;
		if (position.x == 80 && position.y == 58 - 2656)
			cont++;
	}
	if (cont == 6) {
		animation = &run2;
		if (position.x < 130)
			position.x++;
		if (position.y > 0 - 2656)
			position.y--;
		if (position.y == 0 - 2656 && position.x == 130)
			animation = nullptr;
	}
	

	//position.y--;
	//position.x++;
	//animation = &run1;
	//position.x--;
	//position.x--;
	//position.x--;
	//position.y++;
	//position.x--;
	//position.x--;
	
	

}
