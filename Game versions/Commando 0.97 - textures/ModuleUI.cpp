#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleScene1.h"
#include "ModuleTEX.h"
#include "ModuleInput.h"
#include "ModuleUI.h"
#include "ModuleFonts.h"
#include "ModuleAudio.h"
#include "ModuleSaveData.h"

#include <windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
using namespace std;

ModuleUI::ModuleUI()
{

	MarcadorVida.x = 6;
	MarcadorVida.y = 227;
	MarcadorVida.w = 12;
	MarcadorVida.h = 17;

	MarcadorVida2.x = 6;
	MarcadorVida2.y = 208;
	MarcadorVida2.w = 12;
	MarcadorVida2.h = 17;

	vida0.x = 27;
	vida0.y = 6;
	vida0.w = 10;
	vida0.h = 10;


	Inv1.PushBack({ 11, 12, 93, 8 });
	Inv1.PushBack({ 11, 4, 1, 1 });
	Inv1.speed = 0.1;

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

	lvl1.x = 18;
	lvl1.y = 100;
	lvl1.w = 23;
	lvl1.h = 13;

}
ModuleUI::~ModuleUI()
{

}
bool ModuleUI::Start()
{
	bool ret = true;

	LOG("Loading screen UI");

	if (Hud == nullptr) {
		LOG("Cannot load the texture");
		ret = false;
	}
	gate = false;
	var = 0;
	var2 = 0;
	tempo1 = 0;
	return ret;
}

bool ModuleUI::CleanUp()
{
	bool ret = true;

	LOG("Unloading screen UI");


	return true;
}

update_status ModuleUI::Update()
{
	if (tempo1 <= 120) {
		App->render->Blit(App->TEX->Hud2, 111, App->scene_1->current_start_pos + 100 - App->scene_1->cont, &lvl1);
		tempo1++;
	}

	if ((App->player->position.y == (110 - App->scene_1->cont) ||
		App->player->position.y == (2294 - 2656 - App->scene_1->cont) ||
		App->player->position.y == (1836 - 2656 - App->scene_1->cont) ||
		App->player->position.y == (882 - App->scene_1->cont) ||
		App->player->position.y == (395 - App->scene_1->cont))
		&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) {
		if (App->player->GOD == true) {
			current_animation = &Inv1;
			r = current_animation->GetCurrentFrame();
			App->render->Blit(App->TEX->Inv, 110, App->scene_1->current_start_pos + 5 - App->scene_1->cont, &r);
		}
		cont = 1;
		sprintf_s(str1, "%i", score);
		sprintf_s(str2, "%i", grenade);
		sprintf_s(str3, "%i", App->player->vides);
		App->render->Blit(App->TEX->Hud, 116, App->scene_1->current_start_pos + 213 - App->scene_1->cont, &MarcadorGranada);
		if (App->player2->twoplayerson == false)
			App->render->Blit(App->TEX->Hud, 22, App->scene_1->current_start_pos + 210 - App->scene_1->cont, &MarcadorVida);
		if (App->player2->twoplayerson == false)
		App->fonts->BlitText(35, App->scene_1->current_start_pos + 215 - App->scene_1->cont, App->savedata->font_score, str3);
		App->fonts->BlitText(129, App->scene_1->current_start_pos + 215 - App->scene_1->cont, App->savedata->font_score, str2);
		cont = 0;
		App->fonts->BlitText(37, App->scene_1->current_start_pos + 5 - App->scene_1->cont, App->savedata->font_score, str1);
		if (App->player2->twoplayerson == true) {
			if (App->player2->torevive >= 1)
				App->render->Blit(App->TEX->JANE, 22, App->scene_1->current_start_pos + 214 - App->scene_1->cont, &App->player2->torevive2);
			if (App->player2->torevive >= 2)
				App->render->Blit(App->TEX->JANE, 22 + 15, App->scene_1->current_start_pos + 214 - App->scene_1->cont, &App->player2->torevive2);
			if (App->player2->torevive >= 3)
				App->render->Blit(App->TEX->JANE, 22 + 15 + 15, App->scene_1->current_start_pos + 214 - App->scene_1->cont, &App->player2->torevive2);
			if (App->player2->torevive >= 4)
				App->render->Blit(App->TEX->JANE, 22 + 15 + 15 + 15, App->scene_1->current_start_pos + 214 - App->scene_1->cont, &App->player2->torevive2);
		}
	}

		else {
			if (App->player->GOD == true) {
				current_animation = &Inv1;
				r = current_animation->GetCurrentFrame();
				App->render->Blit(App->TEX->Inv, 110, App->scene_1->current_start_pos + 5 - App->scene_1->cont, &r);
			}
			cont = 1;
			sprintf_s(str1, "%i", score);
			sprintf_s(str2, "%i", grenade);
			sprintf_s(str3, "%i", App->player->vides);
			App->render->Blit(App->TEX->Hud, 116, App->scene_1->current_start_pos + 213 - App->scene_1->cont, &MarcadorGranada);
			if (App->player2->twoplayerson == false)
				App->render->Blit(App->TEX->Hud, 22, App->scene_1->current_start_pos + 210 - App->scene_1->cont, &MarcadorVida);
			if (App->player2->twoplayerson == false)
			App->fonts->BlitText(35, App->scene_1->current_start_pos + 215 - App->scene_1->cont, App->savedata->font_score, str3);
			App->fonts->BlitText(129, App->scene_1->current_start_pos + 215 - App->scene_1->cont, App->savedata->font_score, str2);
			cont = 0;
			App->fonts->BlitText(37, App->scene_1->current_start_pos + 5 - App->scene_1->cont, App->savedata->font_score, str1);
			if (App->player2->twoplayerson == true) {
				if (App->player2->torevive >= 1)
					App->render->Blit(App->TEX->JANE, 22, App->scene_1->current_start_pos + 214 - App->scene_1->cont, &App->player2->torevive2);
				if (App->player2->torevive >= 2)
					App->render->Blit(App->TEX->JANE, 22 + 15, App->scene_1->current_start_pos + 214 - App->scene_1->cont, &App->player2->torevive2);
				if (App->player2->torevive >= 3)
					App->render->Blit(App->TEX->JANE, 22 + 15 + 15, App->scene_1->current_start_pos + 214 - App->scene_1->cont, &App->player2->torevive2);
				if (App->player2->torevive >= 4)
					App->render->Blit(App->TEX->JANE, 22 + 15 + 15 + 15, App->scene_1->current_start_pos + 214 - App->scene_1->cont, &App->player2->torevive2);
			}
		}

		return UPDATE_CONTINUE;
	}

