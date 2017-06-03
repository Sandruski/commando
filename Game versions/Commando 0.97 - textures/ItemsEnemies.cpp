#include "Application.h"
#include "ItemsEnemies.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModuleAudio.h"

ItemsEnemies::ItemsEnemies(int x, int y) : Enemy(x, y)
{
	//ITEM DROPPED2
	drop2.PushBack({ 137, 235, 12, 16 });
	drop2.PushBack({ 153, 235, 12, 16 });
	drop2.PushBack({ 168, 235, 12, 16 });
	drop2.PushBack({ 183, 235, 12, 16 });
	drop2.speed = 0.1f;

	animation = &drop2;

	collider = App->collision->AddCollider({ 0, 0, 12, 15 }, COLLIDER_TYPE::COLLIDER_ITEM1, (Module*)App->enemies);
}

void ItemsEnemies::OnCollision(Collider* c1, Collider* c2) {
	App->UI->score += 1000;
	App->audio->play_fx7();

	c2->to_delete;
}