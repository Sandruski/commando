#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleUI.h"
#include "ModuleFonts.h"

#include<stdio.h>
#include<string.h>

ModuleUI::ModuleUI()
{

	MarcadorVida.x = 6;
	MarcadorVida.y = 227;
	MarcadorVida.w = 12;
	MarcadorVida.h = 17;

	vida0.x = 27;
	vida0.y = 6;
	vida0.w = 10;
	vida0.h = 10;


	vida1.x = 40;
	vida1.y = 6;
	vida1.w = 8;
	vida1.h = 10;


	vida2.x = 52;
	vida2.y = 6;
	vida2.w = 12;
	vida2.h = 10;


	vida3.x = 69;
	vida3.y = 6;
	vida3.w = 10;
	vida3.h = 10;

	MarcadorGranada.x = 29;
	MarcadorGranada.y = 229;
	MarcadorGranada.w = 12;
	MarcadorGranada.h = 13;

}
ModuleUI::~ModuleUI()
{

}
bool ModuleUI::Start()
{
	bool ret = true;

	LOG("Loading screen UI");
	font_score = App->fonts->Load("fonts/rtype_font.png", "0123456789", 1);
	Hud = App->textures->Load("items&HUD&snake.png");
	Hud2 = App->textures->Load("Alphabet&Numbers&Extra.png");

	if (Hud == nullptr) {
		LOG("Cannot load the texture");
		ret = false;
	}
	gate = false;
	var = 0;
	var2 = 0;

	return ret;
}

bool ModuleUI::CleanUp()
{
	bool ret = true;

	LOG("Unloading screen UI");
	App->textures->Unload(Hud);

	return false;
}

update_status ModuleUI::Update()
{

	if (App->player->vides >= 3) {

		App->render->Blit(Hud, 22, 210 - var, &MarcadorVida);

		if (App->player->position.y <= 110 && abs(App->player->position.y) == abs(App->render->h)) {
			if (var2 != App->player->position.y)
				var += 1;
		}

		var2 = App->player->position.y;

		if (App->player->vides == 3) {

			App->render->Blit(Hud2, 35, 213 - var, &vida3);

			if (App->player->position.y <= 110 && abs(App->player->position.y) == abs(App->render->h)) {
				if (var2 != App->player->position.y)
					var += 1;
			}

			var2 = App->player->position.y;


		}
		if (App->player->vides == 3) {

			App->render->Blit(Hud, 116, 213 - var, &MarcadorGranada);
			//
			cont = 0;
			char str2[10];
			sprintf_s(str2, "%i", score);
			App->fonts->BlitText(37, 5 - var, font_score, str2);
			//grenades
			cont = 1;
			char str1[10];
			sprintf_s(str1, "%i", grenade);
			App->fonts->BlitText(129, 215 - var, font_score, str1);
			if (App->player->position.y <= 110 && abs(App->player->position.y) == abs(App->render->h)) {
				if (var2 != App->player->position.y)
					var += 1;
			}

			var2 = App->player->position.y;


		}

	}

	if (App->player->vides >= 2) {

		App->render->Blit(Hud, 22, 210 - var, &MarcadorVida);

		if (App->player->position.y <= 110 && abs(App->player->position.y) == abs(App->render->h)) {
			if (var2 != App->player->position.y)
				var += 1;
		}

		var2 = App->player->position.y;

		if (App->player->vides == 2) {

			App->render->Blit(Hud2, 35, 213 - var, &vida2);

			if (App->player->position.y <= 110 && abs(App->player->position.y) == abs(App->render->h)) {
				if (var2 != App->player->position.y)
					var += 1;
			}

			var2 = App->player->position.y;


		}
		if (App->player->vides == 2) {

			App->render->Blit(Hud, 116, 213 - var, &MarcadorGranada);
			//
			cont = 0;
			char str2[10];
			sprintf_s(str2, "%i", score);
			//grenades
			cont = 1;
			char str1[10];
			sprintf_s(str1, "%i", grenade);
			App->fonts->BlitText(129, 215 - var, font_score, str1);
			App->fonts->BlitText(37, 5 - var, font_score, str2);
			if (App->player->position.y <= 110 && abs(App->player->position.y) == abs(App->render->h)) {
				if (var2 != App->player->position.y)
					var += 1;
			}

			var2 = App->player->position.y;


		}



	}

	if (App->player->vides >= 1) {

		App->render->Blit(Hud, 22, 210 - var, &MarcadorVida);

		if (App->player->position.y <= 110 && abs(App->player->position.y) == abs(App->render->h)) {
			if (var2 != App->player->position.y)
				var += 1;
		}

		var2 = App->player->position.y;

		if (App->player->vides == 1) {

			App->render->Blit(Hud2, 35, 213 - var, &vida1);

			if (App->player->position.y <= 110 && abs(App->player->position.y) == abs(App->render->h)) {
				if (var2 != App->player->position.y)
					var += 1;
			}

			var2 = App->player->position.y;


		}
		if (App->player->vides == 1) {

			App->render->Blit(Hud, 116, 213 - var, &MarcadorGranada);
			//score
			cont = 0;
			char str2[10];
			sprintf_s(str2, "%i", score);
			App->fonts->BlitText(37, 5 - var, font_score, str2);
			//grenades
			cont = 1;
			char str1[10];
			sprintf_s(str1, "%i", grenade);
			App->fonts->BlitText(129, 215 - var, font_score, str1);
			if (App->player->position.y <= 110 && abs(App->player->position.y) == abs(App->render->h)) {
				if (var2 != App->player->position.y)
					var += 1;
			}

			var2 = App->player->position.y;


		}



	}


	

	return UPDATE_CONTINUE;
}
