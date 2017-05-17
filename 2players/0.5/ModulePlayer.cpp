#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleScene1.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleSecretRoom1A.h"
#include "ModuleSecretRoomB.h"
#include "ModuleSecretRoomC.h"
#include "ModuleSecretRoomD.h"
#include "ModuleSecretRoomE.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMenu.h"
#include "ModulePlayer2.h"
#include "ModuleUI.h"
#include "ModuleEnding.h"
#include "ModuleParticlesGrenade.h"
#include "ModuleParticlesGrenade1.h"
#include "SDL/include/SDL_timer.h"

//We have to change the position of the end of the bullet and the end of the grenade!

ModulePlayer::ModulePlayer()
{
	// idle animation (arcade sprite sheet)
	idleF.PushBack({ 34, 15, 16, 24 });
	idleF.PushBack({ 48, 15, 15, 26 });

	// idle animation (arcade sprite sheet)
	backward.PushBack({ 4, 16, 16, 26 });
	backward.PushBack({ 20, 15, 15, 26 });

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	forward.PushBack({ 34, 15, 16, 24 });
	forward.PushBack({ 48, 15, 15, 26 });

	right.PushBack({ 200, 13, 19, 28 });
	right.PushBack({ 219, 14, 18, 26 });

	left.PushBack({ 5, 41, 19, 25 });
	left.PushBack({ 23, 42, 19, 25 });

	diagWD.PushBack({ 113, 15, 17, 25 });
	diagWD.PushBack({ 130, 14, 18, 26 });

	diagWA.PushBack({ 165, 14, 19, 27 });
	diagWA.PushBack({ 183, 16, 18, 25 });

	diagSA.PushBack({ 63, 15, 17, 25 });
	diagSA.PushBack({ 148, 16, 17, 24 });

	diagSD.PushBack({ 80, 15, 17, 25 });
	diagSD.PushBack({ 97, 16, 17, 24 });

	invisible.PushBack({ 162, 231, 10, 10 });

	waterDie.PushBack({ 239, 16, 13, 16 });

	grenade.PushBack({ 170, 44, 15, 22 });
	grenade.PushBack({ 188, 44, 16, 24 });
	grenade.speed = 0.04;

	die.PushBack({ 43, 44, 16, 27 });
	die.PushBack({ 62, 39, 15, 27 });
	die.PushBack({ 80, 44, 17, 27 });
	die.speed = 0.02;



}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
		position.x = 130;
		position.y = 110;
	
		help.x = 226;
		help.y = 45;
		help.w = 9;
		help.h = 19;

		dead2player.x = 153;
		dead2player.y = 85;
		dead2player.w = 13;
		dead2player.h = 13;



	collrev = App->collision->AddCollider({ 300, 300, 40, 40 }, COLLIDER_REVIVE, this);
	coll = App->collision->AddCollider({ 300, 300, 12, 15 }, COLLIDER_PLAYER, this); //the collider is out of the screen!
	feetC = App->collision->AddCollider({ 300 - 16, 300 - 19, 8, 4 }, COLLIDER_PLAYER, this);

	p1.x = position.x - 30;
	p1.y = position.y;

	p2.x = position.x;
	p2.y = position.y - 30;

	p3.x = position.x + 30;
	p3.y = position.y;

	p4.x = position.x;
	p4.y = position.y + 30;

	LOG("Loading player textures");
	graphics = App->textures->Load("Assets/Sprites/spritesheet_humanos.png");

	return true;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	if (coll != nullptr)
		coll->to_delete = true;

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	p1.x = position.x - 30;
	p1.y = position.y;

	p2.x = position.x;
	p2.y = position.y - 30;

	p3.x = position.x + 30;
	p3.y = position.y;

	p4.x = position.x;
	p4.y = position.y + 30;

	speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_DOWN && GOD == false)
		GOD = true;
	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_DOWN && GOD == true)
		GOD = false;

	if (App->player->position.y <= 1405 - 2656 && App->player->position.y >= 1338 - 2666) {
		current_animation = &invisible;
	}

	//GRENADE
	//Grenades must be retouched because now if player throws 2 grenades, only kills the last one

	if (cooldown == false && non_grenade == false && App->input->keyboard[SDL_SCANCODE_LSHIFT] == KEY_STATE::KEY_DOWN && App->UI->grenade > 0 && (position.y >= 1405 - 2656 || App->player->position.y <= 1338 - 2666))
	{
		cooldown = true;
		non_grenade = false;
		check_grenade = 0;
		update_position_grenade = 0;
		App->UI->grenade--;

		//Reset player animation throwing a grenade
		grenade.Reset();
		grenade.loops = 0;

		current_animation = &grenade;

		//Reset grenade
		App->particlesgrenade->grenade.anim.Reset();
		App->particlesgrenade->grenade.anim.loops = 0;

		App->particlesgrenade->grenade.speed.x = 0;
		App->particlesgrenade->grenade.speed.y = -2;

		App->particlesgrenade->AddParticle(App->particlesgrenade->grenade, position.x, position.y, COLLIDER_PLAYER_GRENADE, NULL);
	}

	update_position_grenade += App->particlesgrenade->grenade.speed.y;

	if (update_position_grenade == -110) {
		App->particlesgrenade1->grenade.speed.x = 0;
		App->particlesgrenade1->grenade.speed.y = +1;
		App->particlesgrenade1->AddParticle(App->particlesgrenade1->grenade, position.x, position.y - 110, COLLIDER_PLAYER_GRENADE, NULL);
		App->audio->play_fx5();
		cooldown = false;
	}

	if (grenade.loops == 1) {
		current_animation = &forward;
		grenade.loops = 0;
		check_grenade = 1;
	}
	//_grenade_end
	
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT && move == true && check_grenade == 1 && collW == false)
	{
		if (App->player->position.y <= 1405 - 2656 && App->player->position.y >= 1338 - 2666)
			current_animation = &invisible;
		else {
			current_animation = &forward;
			forward.Start();
			revTime = 0;
		}
		
		position.y -= speed;
	}

	else if (App->input->keyboard[SDL_SCANCODE_W] == KEY_UP)
	{
		forward.Stop();
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT && move == true && check_grenade == 1 && collS == false)
	{
		if (App->player->position.y <= 1405 - 2656 && App->player->position.y >= 1338 - 2666)
			current_animation = &invisible;
		else {
			current_animation = &backward;
			backward.Start();
			revTime = 0;
		}


		if (App->fade->on == App->scene_1) {
			if (App->scene_1->start1) {
				if (App->player->position.y <= (2778 - 2656 - App->scene_1->cont + 88)) {
					position.y += speed;
				}
			}
			else if (App->scene_1->start2) {
				if (App->player->position.y <= (2294 - 2656 - App->scene_1->cont + 88)) {
					position.y += speed;
				}
			}
			else if (App->scene_1->start3) {
				if (App->player->position.y <= (1836 - 2656 - App->scene_1->cont + 88)) {
					position.y += speed;
				}
			}
			else if (App->scene_1->start4) {
				if (App->player->position.y <= (882 - 2656 - App->scene_1->cont + 88)) {
					position.y += speed;
				}
			}
			else if (App->scene_1->start5) {
				if (App->player->position.y <= (395 - 2656 - App->scene_1->cont + 88)) {
					position.y += speed;
				}
			}
			else {
				if (App->player->position.y <= (110 - App->scene_1->cont + 88)) {
					position.y += speed;
				}
			}
		}
		else if (App->fade->on == App->room1A) {
			position.y += speed;
		}

	}
	

	else if (App->input->keyboard[SDL_SCANCODE_S] == KEY_UP)
	{
		backward.Stop();
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT && position.x < (SCREEN_WIDTH - right.frames->w) && move == true && check_grenade == 1 && collD == false)
	{
		if (App->player->position.y <= 1405 - 2656 && App->player->position.y >= 1338 - 2666)
			current_animation = &invisible;
		else {
			current_animation = &right;
			right.Start();
		}
		position.x += speed;
		revTime = 0;
	}

	else if (App->input->keyboard[SDL_SCANCODE_D] == KEY_UP)
	{
		right.Stop();
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT && position.x > 0 && move == true && check_grenade == 1 && collA == false)
	{
		if (App->player->position.y <= 1405 - 2656 && App->player->position.y >= 1338 - 2666)
			current_animation = &invisible;
		else {
			current_animation = &left;
			left.Start();
		}
		position.x -= speed;
		revTime = 0;
	}
	else if (App->input->keyboard[SDL_SCANCODE_A] == KEY_UP)
	{
		left.Stop();
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT && move == true && check_grenade == 1) {

		if (App->player->position.y <= 1405 - 2656 && App->player->position.y >= 1338 - 2666)
			current_animation = &invisible;
		else {
			current_animation = &diagWD;
			diagWD.Start();

		}


	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_UP && App->input->keyboard[SDL_SCANCODE_D] == KEY_UP)
	{
		diagWD.Stop();
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT && move == true && check_grenade == 1) {
		if (App->player->position.y <= 1405 - 2656 && App->player->position.y >= 1338 - 2666)
			current_animation = &invisible;
		else {
			current_animation = &diagWA;
		}
		diagWA.Start();

	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_UP && App->input->keyboard[SDL_SCANCODE_A] == KEY_UP)
	{
		diagWA.Stop();
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT && move == true && check_grenade == 1) {
		if (App->player->position.y <= 1405 - 2656 && App->player->position.y >= 1338 - 2666)
			current_animation = &invisible;
		else {
			current_animation = &diagSD;
		}
		diagSD.Start();

	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_UP && App->input->keyboard[SDL_SCANCODE_D] == KEY_UP)
	{
		diagSD.Stop();
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT && move == true && check_grenade == 1) {
		if (App->player->position.y <= 1405 - 2656 && App->player->position.y >= 1338 - 2666)
			current_animation = &invisible;
		else {
			current_animation = &diagSA;
		}
		diagSA.Start();
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_UP && App->input->keyboard[SDL_SCANCODE_A] == KEY_UP)
	{
		diagSA.Stop();
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && current_animation == &diagSA) //Esquerra Abaix
	{
		App->particles->bala.speed.y = +6;
		App->particles->bala.speed.x = -6;
		App->audio->play_fx1();
		App->particles->AddParticle(App->particles->bala, position.x, position.y, COLLIDER_PLAYER_SHOT, NULL);
	}
	else if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && current_animation == &diagSD)//Dreta Abaix
	{
		App->particles->bala.speed.y = +6;
		App->particles->bala.speed.x = +6;
		App->audio->play_fx1();
		App->particles->AddParticle(App->particles->bala, position.x, position.y, COLLIDER_PLAYER_SHOT, NULL);
	}
	else if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && current_animation == &diagWD)//Dreta Adalt
	{
		App->particles->bala.speed.y = -6;
		App->particles->bala.speed.x = +6;
		App->audio->play_fx1();
		App->particles->AddParticle(App->particles->bala, position.x, position.y, COLLIDER_PLAYER_SHOT, NULL);
	}
	else if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && current_animation == &diagWA) //Esquerra Adalt
	{
		App->particles->bala.speed.y = -6;
		App->particles->bala.speed.y = -6;
		App->audio->play_fx1();
		App->particles->AddParticle(App->particles->bala, position.x, position.y, COLLIDER_PLAYER_SHOT, NULL);
	}
	else if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && current_animation == &forward) //Adalt
	{
		App->particles->bala.speed.y = -6;
		App->particles->bala.speed.x = 0;
		App->audio->play_fx1();
		App->particles->AddParticle(App->particles->bala, position.x, position.y, COLLIDER_PLAYER_SHOT, NULL);
	}

	else if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && current_animation == &backward) //Abaix
	{
		App->particles->bala.speed.y = +6;
		App->particles->bala.speed.x = 0;
		App->audio->play_fx1();
		App->particles->AddParticle(App->particles->bala, position.x, position.y, COLLIDER_PLAYER_SHOT, NULL);
	}
	else if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && current_animation == &right) //Dreta
	{
		App->particles->bala.speed.x = +6;
		App->particles->bala.speed.y = 0;
		App->audio->play_fx1();
		App->particles->AddParticle(App->particles->bala, position.x, position.y, COLLIDER_PLAYER_SHOT, NULL);
	}
	else if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && current_animation == &left) //Esquer0a
	{
		App->particles->bala.speed.x = -6;
		App->particles->bala.speed.y = 0;
		App->audio->play_fx1();
		App->particles->AddParticle(App->particles->bala, position.x, position.y, COLLIDER_PLAYER_SHOT, NULL);

	}

	else if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && move == true)
	{
		App->audio->play_fx1();
		App->particles->AddParticle(App->particles->bala, position.x, position.y, COLLIDER_PLAYER_SHOT, NULL);
	}

	r = current_animation->GetCurrentFrame();

	collrev->SetPos(position.x - 12, position.y - 10);
	coll->SetPos(position.x + 2, position.y + 4);
	feetC->SetPos(position.x + 4, position.y + 19);

	if (waterB == false) {
		current_animation = &waterDie;
		move = false;
	}
	currentTime = SDL_GetTicks();
	currentTime -= lastTime;
	if (waterB == true)
		lastTime = SDL_GetTicks();

	if (currentTime > 500 && waterB == false) {
		current_animation = &invisible;
		timeW = true;
	}
	if (enemyB == false) {
		current_animation = &die;
		move = false;
	}
	App->render->Blit(graphics, position.x, position.y, &r);


	collW = false;
	collA = false;
	collS = false;
	collD = false;

	//print help
	if (move == false) {
		detectionlive = 1;
		App->render->Blit(App->player2->graphics, position.x + 10, position.y, &help);
		App->render->Blit(App->player2->graphics, position.x - 2, position.y + 5, &dead2player);
		current_animation = &invisible;
		contdead = 1;
	}
	else if (move == true && contdead == 1) {
		current_animation = &idleF;
		contdead = 0;
		detectionlive = 0;
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{

	if ((c1->type == COLLIDER_PLAYER || c1->type == COLLIDER_PLAYER_FEET) && c2->type == COLLIDER_WALL && GOD == false)
		OnCollisionWall(c1, c2);
	if ((c1->type == COLLIDER_PLAYER || c1->type == COLLIDER_PLAYER_FEET) && c2->type == COLLIDER_WATER && GOD == false)
		OnCollisionWater(c1, c2);
	if ((c1->type == COLLIDER_PLAYER_FEET || c1->type == COLLIDER_PLAYER) && c2->type == COLLIDER_ITEM)
		OnCollisionItem(c1, c2);
	if ((c1->type == COLLIDER_PLAYER && (c2->type == COLLIDER_ENEMY || c2->type == COLLIDER_ENEMY_SHOT) && GOD == false) && detectionlive == 0)
		OnCollisionEnemy(c1, c2);
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_REVIVE2 && App->player2->move == false)
		OnCollisionRev(c1, c2);

}




void ModulePlayer::OnCollisionWall(Collider* c1, Collider* c2)
{
	/*if (App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT)
	position.y += speed;

	else if (App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT)
	position.y -= speed;
	else if (App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT)
	position.x += speed;
	else if (App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT)
	position.x -= speed;*/

	if ((c1->rect.x + c1->rect.w) - c2->rect.x != 1 && (c2->rect.x + c2->rect.w) - c1->rect.x != 1 && (c2->rect.y + c2->rect.h) - c1->rect.y == 1 && (c1->rect.y + c1->rect.h) - c2->rect.y != 1)

		collW = true;

	if ((c1->rect.x + c1->rect.w) - c2->rect.x != 1 && (c2->rect.x + c2->rect.w) - c1->rect.x == 1 && (c2->rect.y + c2->rect.h) - c1->rect.y != 1 && (c1->rect.y + c1->rect.h) - c2->rect.y != 1)

		collA = true;

	if ((c1->rect.x + c1->rect.w) - c2->rect.x != 1 && (c2->rect.x + c2->rect.w) - c1->rect.x != 1 && (c2->rect.y + c2->rect.h) - c1->rect.y != 1 && (c1->rect.y + c1->rect.h) - c2->rect.y == 1)

		collS = true;

	if ((c1->rect.x + c1->rect.w) - c2->rect.x == 1 && (c2->rect.x + c2->rect.w) - c1->rect.x != 1 && (c2->rect.y + c2->rect.h) - c1->rect.y != 1 && (c1->rect.y + c1->rect.h) - c2->rect.y != 1)

		collD = true;
}



void ModulePlayer::OnCollisionItem(Collider* c1, Collider* c2) {

	App->audio->play_fx7();

	if (App->player->position.y < 2655 - 2656 && App->player->position.y > 2547 - 2656)
	detectionitem[0] = true;
	if (App->player->position.y < 2547 - 2656 && App->player->position.y > 2340 - 2656) {
		detectionitem[1] = true;
		App->UI->grenade++;
	}
	if (App->player->position.y < 2016 - 2656 && App->player->position.y > 1829 - 2656) {
		detectionitem[2] = true;
		App->UI->grenade++;
	}
	if (App->player->position.y < 1269 - 2656 && App->player->position.y > 1104 - 2656) {
		detectionitem[3] = true;
	}
	if (App->player->position.y < 1041 - 2656 && App->player->position.y > 896 - 2656) {
		detectionitem[4] = true;
		App->UI->grenade++;
	}
	if (App->player->position.y < 792 - 2656 && App->player->position.y > 613 - 2656) {
		detectionitem[5] = true;
		App->UI->grenade++;
	}
	if (App->player->position.y < 577 - 2656 && App->player->position.y > 416 - 2656) {
		detectionitem[6] = true;
		App->UI->grenade++;
	}
	if (App->player->position.y < 380 - 2656 && App->player->position.y > 212 - 2656) {
		detectionitem[7] = true;
		App->UI->grenade++;
	}
	App->UI->grenade++;
	c2->to_delete = true;

}

void ModulePlayer::OnCollisionWater(Collider* c1, Collider* c2) {

	non_grenade = true;
	App->ending->cont = 0;
	play_ending = true;

	if (App->fade->IsFading() == false)
	{

		if (vides != 0) {
			waterB = false;
			if (timeW == true) {
				vides--;
				App->audio->pause_music();
				App->audio->play_fx6();
				App->particles->AddParticle(App->particles->explosion, position.x + 3, position.y + 5, COLLIDER_END_OF_BULLET, NULL);
				App->scene_1->start = false;
				save_player_position = position.y;
				App->fade->FadeToBlack(App->scene_1, App->scene_1);
			}
		}
		else if (vides == 0) {
			if (timeW == true) {
				App->audio->pause_music();
				App->audio->play_fx6();
				App->particles->AddParticle(App->particles->explosion, position.x + 3, position.y + 5, COLLIDER_END_OF_BULLET, NULL);
				App->scene_1->start = true;
				App->fade->FadeToBlack(App->scene_1, App->ending);
			}
			vides = 3;
		}
	}
}
void ModulePlayer::OnCollisionEnemy(Collider* c1, Collider* c2) {

	if (App->player2->twoplayerson == false) {
		non_grenade = true;
		play_ending = true;
		App->ending->cont = 0;

		if (App->fade->IsFading() == false)
		{

			if (vides != 0) {
				vides--;
				App->audio->pause_music();
				App->audio->play_fx6();
				App->scene_1->start = false;
				save_player_position = position.y;
				App->fade->FadeToBlack(App->scene_1, App->scene_1, 5.0f);
				enemyB = false;

			}

			else if (vides == 0) {
				App->audio->pause_music();
				App->audio->play_fx6();
				App->scene_1->start = true;
				App->fade->FadeToBlack(App->scene_1, App->ending, 5.0f);
				enemyB = false;
				vides = 3;
			}
		}
	}

	else {
		move = false;
		//vides--;
		if (vides != 0) {
			vides--;
		}

	}

}

void ModulePlayer::OnCollisionRev(Collider* c1, Collider* c2)
{
	if (App->input->keyboard[SDL_SCANCODE_9] == KEY_STATE::KEY_REPEAT) {
		App->player2->revTime++;
		/*
		if (revTime == 2) {

		App->render->Blit(graphics, App->player->position.x - 5, App->player->position.y, &hpRev1);
		}
		if (revTime == 4) {

		App->render->Blit(graphics, App->player->position.x - 5, App->player->position.y, &hpRev2);
		}
		if (revTime == 6) {

		App->render->Blit(graphics, App->player->position.x - 5, App->player->position.y, &hpRev3);
		}
		if (revTime == 8) {

		App->render->Blit(graphics, App->player->position.x - 5 , App->player->position.y, &hpRev4);
		}
		if (revTime >= 8) {
		App->player->move = true;
		revTime = 0;
		}
		*/

		if (App->player2->revTime <= 20 && App->player2->revTime >= 1) {

			App->render->Blit(App->player2->graphics, App->player2->position.x - 5, App->player2->position.y, &App->player2->hpRev1);
		}
		else if (App->player2->revTime <= 40 && App->player2->revTime > 20) {

			App->render->Blit(App->player2->graphics, App->player2->position.x - 5, App->player2->position.y, &App->player2->hpRev2);
		}
		else if (App->player2->revTime <= 60 && App->player2->revTime > 40) {

			App->render->Blit(App->player2->graphics, App->player2->position.x - 5, App->player2->position.y, &App->player2->hpRev3);
		}
		else if (App->player2->revTime <= 80 && App->player2->revTime > 60) {

			App->render->Blit(App->player2->graphics, App->player2->position.x - 5, App->player2->position.y, &App->player2->hpRev4);
		}
		if (App->player2->revTime >= 80) {
			App->player2->move = true;
			App->player2->revTime = 0;

		}
	}
	if (App->input->keyboard[SDL_SCANCODE_9] == KEY_STATE::KEY_UP)
		App->player2->revTime = 0;


}