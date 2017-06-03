#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleTEX.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScene1.h"
#include "ModuleUI.h"
#include "ModulePlayer2.h"
#include "ModuleSaveData.h"
#include "ModuleFonts.h"
#include "ModuleTextures.h"
#include <fstream>
#include <iostream>

using namespace std;

ModuleSaveData::ModuleSaveData() : Module()
{}

ModuleSaveData::~ModuleSaveData()
{}


bool ModuleSaveData::Init()
{
	ifstream scorefile;
	scorefile.open("score.txt");
	scorefile >> savescore;
	scorefile.close();
	

	font_score = App->fonts->Load("Assets/fonts/Commando_font.png", "0123456789", 1);
	font_score2 = App->fonts->Load("Assets/fonts/Commando_font2.png", "0123456789", 1);
	return true;
}


update_status ModuleSaveData::Update()
{	
	if (App->fade->on == App->scene_1 && App->player2->twoplayerson == false)
		savescore_p1 = App->UI->score;
	if (savescore < App->UI -> score)
		savescore = App->UI -> score;
	if (App->player2->twoplayerson == true && App->fade->on == App->scene_1) {
		savescore2p = App->UI->score;

	}
	return update_status::UPDATE_CONTINUE;
}

bool ModuleSaveData::CleanUp()
{
	ofstream scorefile2;
	scorefile2.open("score.txt", std::ofstream::out | std::ofstream::trunc);
	scorefile2 << savescore;
	scorefile2.close();
	App->fonts->UnLoad(font_score);
	App->fonts->UnLoad(font_score2);
	
	return true;
}


