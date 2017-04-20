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
#include "ModuleFadeToBlack.h"
#include "ModuleMenu.h"


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

	invisible.PushBack({ 209, 202, 17, 24 });

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	graphics = App->textures->Load("spritesheet_humanos.png");

	position.x = 100;
	position.y = 220;

	coll = App->collision->AddCollider({ 300, 300, 16, 19 }, COLLIDER_PLAYER, this); //the collider is out of the screen!
	feetC = App->collision->AddCollider({ 300, 300, 10, 5 }, COLLIDER_PLAYER, this);
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
	speed = 1;

	if (App->player->position.y <= 1430 - 2656 && App->player->position.y >= 1344 - 2656) {
		current_animation = &invisible;

	}

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT /*&& Wall == true*/)
	{
		if (App->player->position.y <= 1430 - 2656 && App->player->position.y >= 1344 - 2656)
			current_animation = &invisible;
		else {
		current_animation = &forward;
		forward.Start();
		}

		if (position.y > App->render->two - 210) {
			position.y -= speed;
		}
		/*
		if (position.y >= 150)
			position.y -= speed;
		else if (App->scene_1->h == 0 && position.y > 25)
			position.y -= speed;
		*/
	}

	else if (App->input->keyboard[SDL_SCANCODE_W] == KEY_UP)
	{
		forward.Stop();
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT)
	{
		if (App->player->position.y <= 1430 - 2656 && App->player->position.y >= 1344 - 2656)
			current_animation = &invisible;
		else {
		current_animation = &backward;
		backward.Start();
		}
	
		if (position.y <= App->render->two) {
			position.y += speed;
		}
		/*
		if (position.y < 220) {
			position.y += speed;
		}
		*/
	}

	else if (App->input->keyboard[SDL_SCANCODE_S] == KEY_UP)
	{
		backward.Stop();
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT && position.x < (SCREEN_WIDTH - right.frames->w))
	{
		if (App->player->position.y <= 1430 - 2656 && App->player->position.y >= 1344 - 2656)
			current_animation = &invisible;
		else {
		current_animation = &right;
		right.Start();
		}
		position.x += speed;
	}

	else if (App->input->keyboard[SDL_SCANCODE_D] == KEY_UP)
	{
		right.Stop();
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT && position.x > 0)
	{
		if (App->player->position.y <= 1430 - 2656 && App->player->position.y >= 1344 - 2656)
			current_animation = &invisible;
		else {
		current_animation = &left;
		left.Start();
		}
		position.x -= speed;
	}
	else if (App->input->keyboard[SDL_SCANCODE_A] == KEY_UP)
	{
		left.Stop();
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT) {

		if (App->player->position.y <= 1430 - 2656 && App->player->position.y >= 1344 - 2656)
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
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT) {
		if (App->player->position.y <= 1430 - 2656 && App->player->position.y >= 1344 - 2656)
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
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT) {
		if (App->player->position.y <= 1430 - 2656 && App->player->position.y >= 1344 - 2656)
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
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT) {
			if (App->player->position.y <= 1430 - 2656 && App->player->position.y >= 1344 - 2656)
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

	

	if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN && current_animation == &diagSA) //Esquerra Abaix
	{
		App->particles->bala.speed.y = +6;
		App->particles->bala.speed.x = -6;
		App->audio->play_fx1();
		App->particles->AddParticle(App->particles->bala, position.x, position.y, COLLIDER_PLAYER_SHOT, NULL);
	}
	else if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN && current_animation == &diagSD)//Dreta Abaix
	{
		App->particles->bala.speed.y = +6;
		App->particles->bala.speed.x = +6;
		App->audio->play_fx1();
		App->particles->AddParticle(App->particles->bala, position.x, position.y, COLLIDER_PLAYER_SHOT, NULL);
	}
	else if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN && current_animation == &diagWD)//Dreta Adalt
	{
		App->particles->bala.speed.y = -6;
		App->particles->bala.speed.x = +6;
		App->audio->play_fx1();
		App->particles->AddParticle(App->particles->bala, position.x, position.y, COLLIDER_PLAYER_SHOT, NULL);
	}
	else if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN && current_animation == &diagWA) //Esquerra Adalt
	{
		App->particles->bala.speed.y = -6;
		App->particles->bala.speed.y = -6;
		App->audio->play_fx1();
		App->particles->AddParticle(App->particles->bala, position.x, position.y, COLLIDER_PLAYER_SHOT, NULL);
	}
	else if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN && current_animation == &forward) //Adalt
	{
		App->particles->bala.speed.y = -6;
		App->particles->bala.speed.x = 0;
		App->audio->play_fx1();
		App->particles->AddParticle(App->particles->bala, position.x, position.y, COLLIDER_PLAYER_SHOT, NULL);
	}

	else if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN && current_animation == &backward) //Abaix
	{
		App->particles->bala.speed.y = +6;
		App->particles->bala.speed.x = 0;
		App->audio->play_fx1();
		App->particles->AddParticle(App->particles->bala, position.x, position.y, COLLIDER_PLAYER_SHOT, NULL);
	}
	else if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN && current_animation == &right) //Dreta
	{
		App->particles->bala.speed.x = +6;
		App->particles->bala.speed.y = 0;
		App->audio->play_fx1();
		App->particles->AddParticle(App->particles->bala, position.x, position.y, COLLIDER_PLAYER_SHOT, NULL);
	}
	else if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN && current_animation == &left) //Esquer0a
	{
		App->particles->bala.speed.x = -6;
		App->particles->bala.speed.y = 0;
		App->audio->play_fx1();
		App->particles->AddParticle(App->particles->bala, position.x, position.y, COLLIDER_PLAYER_SHOT, NULL);

	}

	else if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN)
	{
		App->audio->play_fx1();
		App->particles->AddParticle(App->particles->bala, position.x, position.y, COLLIDER_PLAYER_SHOT, NULL);
	}
	
	SDL_Rect r = current_animation->GetCurrentFrame();

	coll->SetPos(position.x, position.y - 24);
	feetC->SetPos(position.x + 3, position.y - 5);


	if (destroyed == false)
		App->render->Blit(graphics, position.x, position.y - 24, &r);


	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_WALL)
		OnCollisionWall(c1, c2);
	else if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_WATER)
		OnCollisionWater(c1, c2);
	else if (c1->type == COLLIDER_PLAYER_FEET && c2->type == COLLIDER_ITEM)
		OnCollisionItem(c1, c2);
	else if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ITEM)
		OnCollisionEnemy(c1, c2);

}



void ModulePlayer::OnCollisionWall(Collider* c1, Collider* c2)
{
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT){
		position.y += speed;
	}
	/*else*/ if (App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT)
		position.y -= speed;
	/*else*/ if (App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT)
		position.x += speed;
	/*else*/ if (App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT)
		position.x -= speed;
}


void ModulePlayer::OnCollisionItem(Collider* c1, Collider* c2) {



}

void ModulePlayer::OnCollisionWater(Collider* c1, Collider* c2) {

	if (destroyed == false && App->fade->IsFading() == false)
	{
		vides--;
		if (vides != 0) {
			//App->particles->AddParticle(WaterD, position.x, position.y, COLLIDER_NONE, NULL);
			App->particles->AddParticle(App->particles->explosion, position.x - 6, position.y - 5, COLLIDER_NONE, NULL);
			App->fade->FadeToBlack(App->scene_1, App->scene_1);

			destroyed = true;
		}
	
	else if (vides == 0) {
		App->particles->AddParticle(App->particles->explosion, position.x - 6, position.y - 5, COLLIDER_NONE, NULL);
		App->fade->FadeToBlack(App->scene_1, App->Menu);
	}
}
}
void ModulePlayer::OnCollisionEnemy(Collider* c1, Collider* c2) {

	/*c1->type == COLLIDER_WALL;
	c2->type == COLLIDER_PLAYER;

	c1->rect.*/

}