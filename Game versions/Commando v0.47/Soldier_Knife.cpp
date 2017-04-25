#include "Application.h"
#include "Soldier_Knife.h"
#include "ModuleCollision.h"
#include "Path.h"

Enemy_SoldierKnife::Enemy_SoldierKnife(int x, int y) : Enemy(x, y)
{
	//ANIMATION TURN (SOLDIER WITH RIFLE)
	//moving to the left
	right.PushBack({ 198, 188, 16, 22 }); //dreta
	right.PushBack({ 3, 229, 16, 22 }); //dreta
	left.PushBack({ 24, 229, 16, 22 }); //esquerra
	left.PushBack({ 219, 199, 16, 22 }); //esquerra
	down.PushBack({ 199, 219, 18, 18 }); //abaix
	down.PushBack({ 225, 219, 13, 23 }); //abaix

	right.speed = 0.5f;
	left.speed = 0.5f;
	down.speed = 0.5f;


	//animation = &right;
	path.PushBack({ 0.5f, 0.0f }, 50);
	//animation = &down;
	path.PushBack({ 0.0f, -0.5f }, 25);
	//animation = &right;
	path.PushBack({ 0.5f, 0.0f }, 25);

	//animation = &left;
	path1.PushBack({ -0.5f, 0.0f }, 50);
	//animation = &down;
	path1.PushBack({ 0.0f, -0.5f }, 25);
	//animation = &left;
	path1.PushBack({ -0.5f, 0.0f }, 25);
	
	original_pos.x = x;
	original_pos.y = y;
	animation = &right;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_SoldierKnife::Move()
{
	
	//if (original_pos.x <= 100) {
	//	position = original_pos + path.GetCurrentPosition(&animation);
	//}
	//else if (original_pos.x > 100) {
		//position = original_pos + path1.GetCurrentPosition(&animation);
	//}
	if (position.x < 140 && cont == 0) {
		position.x++;
		cont = 1;
	}
	else if (position.y > 2085 - 2656 && cont == 1) {
		position.y++;
		cont = 3;
	}
	else if (position.x < 300 && cont == 3) {
		position.y++;
	}
	
	
}
