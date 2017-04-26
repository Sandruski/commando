#include "Application.h"
#include "Soldier_Knife.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleUI.h"
#include "SDL/include/SDL_timer.h"
#include "Path.h"

Enemy_SoldierKnife::Enemy_SoldierKnife(int x, int y) : Enemy(x, y)
{
	//ANIMATION TURN (SOLDIER WITH RIFLE)
	//moving to the left
	right.PushBack({ 198, 188, 16, 22 }); //dreta
	right.PushBack({ 3, 229, 16, 22 }); //dreta
	left.PushBack({ 24, 229, 16, 22 }); //esquerra
	left.PushBack({ 219, 188, 16, 22 }); //esquerra
	down.PushBack({ 199, 219, 18, 18 }); //abaix
	down.PushBack({ 225, 219, 13, 23 }); //abaix

	right.speed = 0.05f;
	left.speed = 0.05f;
	down.speed = 0.05f;


	die.PushBack({ 6, 111, 16, 27 });
	die.PushBack({ 40, 104, 15, 27 });
	die.PushBack({ 25, 111, 16, 27 });
	die.PushBack({ 40, 104, 15, 27 });

	/*//animation = &right;
	path.PushBack({ +0.5f, +0.0f }, 50);
	//animation = &down;
	path.PushBack({ +0.0f, -0.5f }, 25);
	//animation = &right;
	path.PushBack({ +0.5f, +0.0f }, 25);

	//animation = &left;
	path1.PushBack({ -0.5f, +0.0f }, 50);
	//animation = &down;
	path1.PushBack({ +0.0f, -0.5f }, 25);
	//animation = &left;
	path1.PushBack({ -0.5f, +0.0f }, 25);*/

	original_pos.x = x;
	original_pos.y = y;
	animation = &left;


	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_SoldierKnife::Move()
{
	/*if (original_pos.x <= 100) {
	animation = &right;
	position = original_pos + path.GetCurrentPosition(&animation);
	}
	if (original_pos.x >= 100) {
	animation = &left;
	position = original_pos + path1.GetCurrentPosition(&animation);
	}*/


	currentTime = SDL_GetTicks();
	currentTime -= lastTime;

	if (dieB == false) {
		lastTime = SDL_GetTicks();

		if (App->player->position.y <= -450 || move == true) {
			if (position.x <= 240 && cont == 0) {
				position.x--;
				animation = &left;
				move = true;
				if (position.x == 150)
					cont = 1;
			}
			if (position.y >= -581 && cont == 1) {
				animation = &down;
				position.y++;

				if (position.y == -525)
					cont = 3;

			}
			if (position.x >= 150 && cont == 3) {
				position.x++;
				animation = &right;
				if (position.x == 240)
					cont = 0;
			}
		}

	}

	if (dieB == true) {
		animation = &die;
		die.speed = 0.1f;
		if (currentTime > 800)
			Esperanza = false;
	}

}

void Enemy_SoldierKnife::OnCollision(Collider* c1, Collider* c2) {

	if (dieB == false) {
		if (c2->type == COLLIDER_PLAYER_SHOT)
			App->UI->score += 75;
		else if (c2->type == COLLIDER_END_OF_GRENADE)
			App->UI->score += 150;
	}
	dieB = true;
}
