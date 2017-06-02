#include "Application.h"
#include "Soldier_Shield.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_timer.h"
#include <stdlib.h>
#include <time.h>
#include "ModuleUI.h"
#include "ModuleScene1.h"

Enemy_SoldierShield::Enemy_SoldierShield(int x, int y) : Enemy(x, y)
{
	//ANIMATION MOVE (SOLDIER WITH SHIELD)
	move1.PushBack({ 23, 147, 16, 22 });
	move1.PushBack({ 41, 147, 16, 22 });
	move2.PushBack({ 59, 147, 14, 17 });
	move2.PushBack({ 6, 147, 15, 20 });

	move3.PushBack({ 23, 171, 16, 22 });
	move3.PushBack({ 41, 170, 16, 22 });
	move4.PushBack({ 6, 169, 15, 20 });
	move4.PushBack({ 60, 171, 14, 17 });

	//ANIMATION SOLDIER SURRENDERING
	surrender.PushBack({ 75, 147, 16, 31 });
	surrender.PushBack({ 95, 147, 13, 32 });

	//this soldier has the same dying animation than normal soldiers (even though it's green)

	move1.speed = 0.05f;
	move2.speed = 0.05f;
	move3.speed = 0.05f;
	move4.speed = 0.05f;
	surrender.speed = 0.05f;

	die.PushBack({ 151, 149, 16, 27 });
	die.PushBack({ 40, 104, 15, 27 });
	die.PushBack({ 169, 149, 16, 27 });
	die.PushBack({ 204, 140, 15, 27 });

	animation = &move1;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_SoldierShield::Move()
{
	currentTime = SDL_GetTicks();
	currentTime -= lastTime;
	contt++;

	if (check) {
		if (dieB == false) {
			lastTime = SDL_GetTicks();
			//if (App->player->position.x <= 240 - 2656) {
			aleatori = rand() % 10;
			cont2++;
			if (cont2 > 25 && cont2 < 45) {
				animation = &move4;
			}
			else if (cont2 > 70 && cont2 < 100) {
				animation = &move2;
			}
			else if (cont2 > 170 && cont2 < 220) {
				animation = &move4;
			}
			else if (cont2 > 280 && cont2 < 335) {
				animation = &move2;
			}
			else if (cont2 > 400 && cont2 < 430) {
				animation = &move4;
			}
			else if (cont2 >= 430 && cont2 < 550 || cont2 <= 25 || (cont2 >= 45 && cont2 <= 70) || (cont2 >= 100 && cont2 <= 170) || (cont2 >= 200 && cont2 <= 280) || (cont2 >= 335 && cont2 <= 400)) {
				if (cont == 0 && position.x < 147) {
					animation = &move1;
					position.x++;
					if (position.x >= 147) {
						cont = 1;
					}
				}

				if (cont == 1 && position.x > 97) {
					animation = &move3;
					position.x--;
					if (position.x <= 97) {
						cont = 0;
					}
				}
			}
			if (cont2 >= 550)
				cont2 = 0;
			//else if (cont2 >= 550 /*&& cont2 < 700*/) {
			/*animation = &surrender;
			collider->to_delete = true;
			}*/
			//else if (cont2 >= 700) { animation = nullptr; }
		}
	}

	if (contt > 1800) {
		App->scene_1->TE = false;
	}

	if ((dieB == true || contt > 2000) && App->render->camera.y == ((2880 - SCREEN_HEIGHT)*SCREEN_SIZE) - App->scene_1->speed) {
		animation = &surrender;
		collider->to_delete = true;
		App->player->coll->to_delete = true;
		App->player->feetC->to_delete = true;
		App->player2->coll->to_delete = true;
		App->player2->feetC->to_delete = true;
		App->scene_1->winB = true;
		/*animation = &die;
		die.speed = 0.1f;
		if (currentTime > 1000)
		Esperanza = false;*/
		check = false;

		//player walks towards the door
		App->player->move = false;
		App->player2->move = false;
		App->scene_1->dead = true;
	}

}

void Enemy_SoldierShield::OnCollision(Collider* c1, Collider* c2) {

	if (dieB == false)
		App->UI->score += 150;
	dieB = true;

}