#include "Application.h"
#include "ItemsEnemies2.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModuleAudio.h"

ItemsEnemies2::ItemsEnemies2(int x, int y) : Enemy(x, y)
{
	//ITEM DROPPED1
	drop1.PushBack({ 124, 129, 12, 15 });
	drop1.PushBack({ 140, 129, 12, 15 });
	drop1.PushBack({ 158, 129, 12, 15 });
	drop1.PushBack({ 176, 129, 12, 15 });
	drop1.speed = 0.1f;

	animation = &drop1;

	collider = App->collision->AddCollider({ 0, 0, 12, 15 }, COLLIDER_TYPE::COLLIDER_ITEM1, (Module*)App->enemies);
}

void ItemsEnemies2::OnCollision(Collider* c1, Collider* c2) {
	App->UI->score += 1000;
	App->audio->play_fx7();

	c2->to_delete;
}