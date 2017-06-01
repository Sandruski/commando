#include "Application.h"
#include "Soldier_Knife.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleUI.h"
#include "SDL/include/SDL_timer.h"
#include "Path.h"
#include "ModuleParticles.h"

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

	down_left.PushBack({ 91, 229, 15, 22 }); //abaix
	down_left.PushBack({ 113, 229, 15, 22 }); //abaix

	down_right.PushBack({ 47, 229, 15, 22 }); //abaix
	down_right.PushBack({ 69, 229, 15, 22 }); //abaix

	right.speed = 0.05f;
	left.speed = 0.05f;
	down.speed = 0.05f;

	die.PushBack({ 6, 111, 16, 27 });
	die.PushBack({ 40, 104, 15, 27 });
	die.PushBack({ 25, 111, 16, 27 });
	die.PushBack({ 40, 104, 15, 27 });

	path.PushBack({ +0.9f, +0.0f }, 140);
	path.PushBack({ +0.01f, +0.0f }, 15);
	path.PushBack({ +0.9f, +0.9f }, 20);
	path.PushBack({ +0.01f, +0.01f }, 15);
	path.PushBack({ +0.9f, +0.0f }, 30);
	path.PushBack({ +0.01f, +0.0f }, 15);
	path.PushBack({ +0.0f, +0.9f }, 20);
	path.PushBack({ +0.0f, +0.01f }, 15);
	path.PushBack({ -0.9f, +0.0f }, 60);
	path.PushBack({ -0.01f, +0.0f }, 15);
	path.PushBack({ +0.0f, +0.9f }, 20);
	path.PushBack({ +0.0f, +0.01f }, 15);
	path.PushBack({ -0.9f, +0.0f }, 30);
	path.PushBack({ -0.01f, +0.0f }, 15);
	path.PushBack({ -0.9f, +0.9f }, 30);
	path.PushBack({ -0.1f, +0.1f }, 15);
	path.PushBack({ +0.9f, +0.9f }, 40);
	path.PushBack({ +0.1f, +0.1f }, 15);
	path.PushBack({ +0.0f, +0.9f }, 10);
	path.PushBack({ +0.0f, +0.1f }, 15);
	path.PushBack({ +0.9f, +0.0f }, 300);

	path1.PushBack({ -0.9f, +0.0f }, 80);
	path1.PushBack({ -0.01f, +0.0f }, 15);
	path1.PushBack({ +0.0f, +0.9f }, 10);
	path1.PushBack({ +0.0f, +0.01f }, 15);
	path1.PushBack({ -0.9f, +0.9f }, 30);
	path1.PushBack({ -0.01f, +0.01f }, 15);
	path1.PushBack({ -0.9f, +0.0f }, 90);
	path1.PushBack({ -0.01f, +0.0f }, 15);
	path1.PushBack({ +0.0f, +0.9f }, 20);
	path1.PushBack({ +0.0f, +0.01f }, 15);
	path1.PushBack({ +0.9f, +0.0f }, 100);
	path1.PushBack({ +0.01f, +0.0f }, 15);
	path1.PushBack({ +0.9f, +0.9f }, 20);
	path1.PushBack({ +0.01f, +0.01f }, 15);
	path1.PushBack({ +0.9f, +0.0f }, 50);
	path1.PushBack({ +0.01f, +0.0f }, 15);
	path1.PushBack({ +0.0f, +0.9f }, 10);
	path1.PushBack({ +0.0f, +0.01f }, 15);

	original_pos.x = x;
	original_pos.y = y;
	animation = &left;


	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_SoldierKnife::Move()
{
	currentTime = SDL_GetTicks();
	currentTime -= lastTime;

	if (dieB == false) {
		lastTime = SDL_GetTicks();



		if (original_pos.x < SCREEN_WIDTH / 2) {

			position = original_pos + path.GetCurrentPositionfl(&animation);
			save_step = path.GetCurrentPositionf();
		}

		if (original_pos.x > SCREEN_WIDTH / 2) {

			position = original_pos + path1.GetCurrentPositionfl(&animation);
			save_step = path1.GetCurrentPositionf();
		}

	}

	//ANIMATION CHANGE FOR PATHS
	if ((save_step.x == 0 && save_step.y > 0)) {
		animation = &down;
	}
	else if ((save_step.x == 0 && save_step.y < 0)) {
		animation = &up;
	}
	else if ((save_step.x > 0 && save_step.y == 0)) {
		animation = &right;
	}
	else if ((save_step.x < 0 && save_step.y == 0)) {
		animation = &left;
	}
	else if ((save_step.x > 0 && save_step.y > 0)) {
		animation = &down_right;
	}
	else if ((save_step.x < 0 && save_step.y > 0)) {
		animation = &down_left;
	}
	//

	if (dieB == true) {
		animation = &die;
		die.speed = 0.1f;
		if (currentTime > 800)
			Esperanza = false;
	}

}

void Enemy_SoldierKnife::OnCollision(Collider* c1, Collider* c2) {

	App->particles->AddParticle(App->particles->dieEnemie, c1->rect.x, c1->rect.y, COLLIDER_ENEMYDIE, NULL);

}
