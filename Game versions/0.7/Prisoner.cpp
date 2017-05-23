#include "Application.h"
#include "Prisoner.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModulePlayer.h"
#include "ModuleSecretRoomE.h"
#include "ModuleFadeToBlack.h"



Enemy_Prisoner::Enemy_Prisoner(int x, int y) : Enemy(x, y)
{
	//ANIMATION ANIMATED (PRISONER)
	animated.PushBack({ 61, 195, 15, 22 });
	animated.PushBack({ 79, 195, 15, 22 });
	animated.PushBack({ 96, 195, 15, 22 });

	//ANIMATION STAND1 (PRISONER)
	stand1.PushBack({ 151, 195, 16, 22 });

	//ANIMATION STAND2 (PRISONER)
	stand2.PushBack({ 151, 195, 16, 22 });
	stand2.PushBack({ 169, 195, 16, 22 });

	//ANIMATION RUN (PRISONER)
	run.PushBack({ 114, 195, 16, 32 });
	run.PushBack({ 133, 195, 16, 31 });

	runPowerUp.PushBack({ 189, 151, 16, 31 });
	runPowerUp.PushBack({ 219, 151, 16, 31 });

	animated.speed = 0.1f;
	stand2.speed = 0.13f;
	run.speed = 0.1f;	
	runPowerUp.speed = 0.1f;

	animation = &stand1;

	collider = App->collision->AddCollider({ 0, 0, 18, 8 }, COLLIDER_TYPE::COLLIDER_PRISONER, (Module*)App->enemies);
}

void Enemy_Prisoner::Move()
{
	//Animation
	cont++;
	if (cont == 130) {
		animation = &stand2;
	}

	if (cont == 230) {
		animation = &stand1;
		cont = 0;
	}
	//

	if (move == true)
	{
		if (App->player->SoldierPowerUp == 1 || App->player->SoldierPowerUp == 2) {
			animation = &runPowerUp;
			App->player->GunPowerUp = true;
			App->player->SoldierPowerUp = 2;

		}
		else
			animation = &run;
		position.x++;

	}
}


void Enemy_Prisoner::OnCollision(Collider* c1, Collider* c2) {
	if (move == false)
		App->UI->score += 1000;
	move = true;
}