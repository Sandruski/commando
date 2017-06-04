#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleScene1.h"
#include "ModuleCinematic.h"
#include "ModuleMenu.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleEND.h"
#include "ModuleTEX.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEndinglvl1.h"
#include "ModuleCinematicRadio.h"



ModuleCinematicRadio::ModuleCinematicRadio()
{
	background2.x = 0;
	background2.y = 0;
	background2.w = 256;
	background2.h = 1728;

	

	playerenter.PushBack({ 155, 206, 15, 20 });
	playerenter.PushBack({ 173, 210, 12, 14 });



	invisible.PushBack({ 1,1,1,1 });
	invisible.PushBack({ 1,1,1,1 });


	playerleft.PushBack({ 5, 41, 19, 25 });
	playerleft.PushBack({ 23, 42, 19, 25 });
	playerleft.speed = 0.05f;

	helicopter1.PushBack({ 170, 49, 166, 127 });
	helicopter1.PushBack({ 168, 190, 166, 127 });
	helicopter1.PushBack({ 404, 90, 166, 127 });
	helicopter1.speed = 0.2f;

	helicopter3.PushBack({ 404, 289, 166, 127 });
	helicopter3.PushBack({ 405, 505, 166, 127 });
	helicopter3.PushBack({ 405, 782, 166, 127 });
	helicopter3.speed = 0.2f;

	helicopter2.PushBack({ 755, 160, 166, 161 });
	helicopter2.PushBack({ 752, 370, 166, 161 });
	helicopter2.PushBack({ 762, 798, 166, 161 });
	helicopter2.speed = 0.2f;
}

ModuleCinematicRadio::~ModuleCinematicRadio()
{}

// Load assets
bool ModuleCinematicRadio::Start()
{

	check = true;
	helialtura = 220;
	w = 0, h = SCREEN_HEIGHT - 1728;
	helicont = 0;
	sj_y = 86, sj_x = 260;
	pjcont = 0;
	App->render->camera.y = 0;

	//Initialize audio
	check_audio = true;
	App->audio->play_music8();

	LOG("Loading cinematic scene");
	

	return true;
}

// UnLoad assets
bool ModuleCinematicRadio::CleanUp()
{
	LOG("Unloading 1st scene");

	App->player->move = false;
	helicont = 0;

	return true;
}

// Update: draw background
update_status ModuleCinematicRadio::Update()
{
	update_status ret = UPDATE_CONTINUE;

	
	App->render->Blit(App->TEX->graphics2, w, h, &background2);


	if (check_audio) {
		App->audio->play_fx12();
		check_audio = false;
	}

	

	if (helicont < 350) {
		current_animation = &helicopter1;
		r = current_animation->GetCurrentFrame();
		App->render->Blit(App->TEX->helicopter, 128 - 80, helialtura, &r);
		helicont++;
		if (helialtura > 10)
			helialtura--;
	}
	else if (helicont >= 350 && helicont < 370) {
		current_animation = &helicopter2;
		r = current_animation->GetCurrentFrame();
		App->render->Blit(App->TEX->helicopter, 128 - 80, helialtura - 20, &r);
		helicont++;
	}
	else if (helicont >= 370 && helicont < 410) {
		//helicopter alt i adeu
		current_animation = &helicopter3;
		r = current_animation->GetCurrentFrame();
		App->render->Blit(App->TEX->helicopter, 128 - 80, helialtura - 10, &r);
		helicont++;
	}
	//else if (helicont >= 410 && helicont < 430) {
	//	current_animation = &helicopter1;
	//	r = current_animation->GetCurrentFrame();
	//	App->render->Blit(helicopter, 128 - 80, helialtura, &r);
	//}
		

	
		if (helicont >= 370 < 565) {
			if (pjcont == 0) {
				//if (contadorsalto == true) {
				sj_y--;
				sj_x++;
				if (sj_y < 70)
					pjcont = 1;
				//	contadorsalto = false;
				//}
			}
			if (pjcont == 1) {
				sj_y++;
				sj_x++;

				if (sj_y >= 90)
					pjcont = 2;
			}
			
		}
	
	if (helicont >= 200 && helicont <= 360) {
		current_animation = &playerleft;
		r = current_animation->GetCurrentFrame();
		App->render->Blit(App->TEX->playerhelicopter, sj_x, sj_y + 1, &r);
		if (sj_x >= 139)
			sj_x--;
		
	}
	if (helicont >= 360 && helicont <= 400) {
		current_animation = &playerenter;
		r = current_animation->GetCurrentFrame();
		App->render->Blit(App->TEX->playerhelicopter, sj_x, sj_y + 1, &r);
		if (sj_x >= 139)
			sj_x--;
	
		
	}

	

	if (helicont >= 280) {
		current_animation = &invisible;

		r = current_animation->GetCurrentFrame();
		App->render->Blit(App->TEX->helicopter, 128 - 80, helialtura, &r);
	
		
	}

	if (helicont >= 350 && helicont <= 1850) {
		App->render->camera.y += 1;
		
		}
	if (helicont >= 410 && helicont <= 2100) {
		helicont++;
		current_animation = &helicopter1;
		r = current_animation->GetCurrentFrame();
		App->render->Blit(App->TEX->helicopter, 128 - 80, helialtura - 10, &r);
		helialtura -= 1;
	}

	if (helicont >= 2000)
		App->fade->FadeToBlack(this, App->EndingLvl1, 1);




	return ret;
}