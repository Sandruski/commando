#include "Application.h"
#include "Soldier_Grenade.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "SDL/include/SDL_timer.h"

Enemy_SoldierGrenade::Enemy_SoldierGrenade(int x, int y) : Enemy(x, y)
{
	//ANIMATION TURN (SOLDIER WHO THROWS GRENADES)

	turn.PushBack({ 56, 110, 16, 22 }); //normal
	turn.PushBack({ 74, 110, 16, 22 }); //down
	turn.PushBack({ 91, 110, 16, 22 }); //MORE down

	turn.speed = 0.1f;

	die.PushBack({ 6, 111, 16, 27 });
	die.PushBack({ 40, 104, 15, 27 });
	die.PushBack({ 25, 111, 16, 27 });
	die.PushBack({ 40, 104, 15, 27 });

	animation = &turn;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_SoldierGrenade::Move()
{
	currentTime = SDL_GetTicks();
	currentTime -= lastTime;

	if (dieB == false) 
		lastTime = SDL_GetTicks();


	if (dieB == true) {

		animation = &die;
		die.speed = 0.1f;
		if (currentTime > 800)
			Esperanza = false;

	}
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

void Enemy_SoldierGrenade::OnCollision(Collider* c1, Collider* c2) {
	if (dieB == false) {
		if (c2->type == COLLIDER_PLAYER_SHOT)
			App->UI->score += 75;
		else if (c2->type == COLLIDER_END_OF_GRENADE)
			App->UI->score += 150;
	}
	dieB = true;


}
