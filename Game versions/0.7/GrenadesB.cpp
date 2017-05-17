#include "Application.h"
#include "GrenadesB.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModuleAudio.h"

GrenadesB::GrenadesB(int x, int y) : Enemy(x, y)
{
	//ANIMATION SHINE (GRENADE)
	shine.PushBack({ 239, 125, 15, 7 });
	shine.PushBack({ 239, 141, 15, 7 });
	shine.PushBack({ 239, 157, 15, 7 });
	shine.PushBack({ 239, 182, 15, 7 });
	shine.speed = 0.2f;

	animation = &shine;

	collider = App->collision->AddCollider({ 0, 0, 15, 7 }, COLLIDER_TYPE::COLLIDER_ITEM, (Module*)App->enemies);
}

void GrenadesB::OnCollision(Collider* c1, Collider* c2) {
	App->UI->grenade += 2;
	App->audio->play_fx7();
}