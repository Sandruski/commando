#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
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

using namespace std;

ModuleSaveData::ModuleSaveData() : Module()
{

}

ModuleSaveData::~ModuleSaveData()
{

}


bool ModuleSaveData::Init()
{
	scorefile.open("score.txt");
	scorefile >> savescore;
	scorefile.close();
	Hud2 = App->textures->Load("Assets/Sprites/Alphabet&Numbers&Extra.png");
	font_score = App->fonts->Load("Assets/fonts/Commando_font.png", "0123456789", 1);
	font_score2 = App->fonts->Load("Assets/fonts/Commando_font2.png", "0123456789", 1);
	return true;
}


update_status ModuleSaveData::Update()
{	
	if(savescore_p1 < App->UI->score)
		savescore_p1 = App->UI->score;
	if (savescore < App->UI->score)
		savescore = App->UI->score;

	if (App->player2->twoplayerson == true && App->fade->on == App->scene_1) {
		savescore2p = App->UI->score;

	}
	return update_status::UPDATE_CONTINUE;
}

bool ModuleSaveData::CleanUp()
{
	scorefile.open("score.txt", std::ofstream::out | std::ofstream::trunc);
	scorefile << savescore;
	scorefile.close();
	App->textures->Unload(Hud2);
	App->fonts->UnLoad(font_score);
	App->fonts->UnLoad(font_score2);
	
	return true;
}


