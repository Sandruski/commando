#include "Application.h"
#include "Crazy_Green.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModuleUI.h"
#include "ModuleParticles.h"
#include <stdlib.h>
#include <time.h>

#include "SDL/include/SDL_timer.h"

Enemy_CrazyGreen::Enemy_CrazyGreen(int x, int y) : Enemy(x, y)
{
	//ANIMATION RUN (CRAZY GREEN SOLDIER)
	left.PushBack({ 112, 147, 15, 23 }); //left
	left.PushBack({ 131, 147, 19, 22 });

	right.PushBack({ 112, 171, 15, 23 }); //right
	right.PushBack({ 131, 171, 19, 22 });

	//ANIMATION OF CRAZY GREEN SOLDIER DYING (green soldier)
	die.PushBack({ 152, 150, 16, 24 });
	die.PushBack({ 170, 150, 16, 24 });
	die.PushBack({ 207, 147, 10, 8 }); //skull

	left.speed = 0.05f;
	right.speed = 0.05f;
	die.speed = 0.1f;

	path.PushBack({ +0.0f, +0.8f }, 40);
	path.PushBack({ +0.8f, +0.8f }, 20);
	path.PushBack({ -0.8f, +0.8f }, 20);
	path.PushBack({ +0.8f, +0.8f }, 20);
	path.PushBack({ +0.0f, +0.8f }, 10);
	path.PushBack({ -0.8f, +0.8f }, 30);
	path.PushBack({ -0.8f, +0.0f }, 20);
	path.PushBack({ +0.8f, +0.8f }, 30);
	path.PushBack({ +0.8f, -0.8f }, 50);
	path.PushBack({ -0.8f, +0.0f }, 40);
	path.PushBack({ +0.0f, -0.8f }, 70);
	path.PushBack({ +0.0f, +0.8f }, 20);
	path.PushBack({ +0.8f, +0.0f }, 300);

	animation = &left;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_CrazyGreen::Move()
{
	currentTime = SDL_GetTicks();
	currentTime -= lastTime;

	if (dieB == false) {
		position = original_pos + path.GetCurrentPositionfl(&animation);
		save_step = path.GetCurrentPositionf(); //it returns an fPoint of the speed of the current step
	}

	//ANIMATION CHANGE FOR PATHS
	if (dieB == false) {
		if ((save_step.x == 0 && save_step.y > 0)) {
			animation = &right;
		}
		else if ((save_step.x == 0 && save_step.y < 0)) {
			animation = &right;
		}
		else if ((save_step.x > 0 && save_step.y == 0)) {
			animation = &right;
		}
		else if ((save_step.x < 0 && save_step.y == 0)) {
			animation = &left;
		}
		else if ((save_step.x > 0 && save_step.y > 0)) {
			animation = &right;
		}
		else if ((save_step.x < 0 && save_step.y > 0)) {
			animation = &left;
		}
		else if ((save_step.x > 0 && save_step.y < 0)) {
			animation = &right;
		}
		else if ((save_step.x < 0 && save_step.y < 0)) {
			animation = &left;
		}
	}

}

void Enemy_CrazyGreen::OnCollision(Collider* c1, Collider* c2) {

	if (dieB == false) {
		App->UI->score += 2000;
		App->audio->play_fx4();
		dieB = true;
		App->particles->AddParticle(App->particles->dieEnemie, collider->rect.x, collider->rect.y, COLLIDER_ENEMYDIE, NULL);
	}

}