#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScene2.h"
#include "ModuleUI.h"
#include "ModuleSaveData.h"
#include "ModuleFonts.h"
#include "ModuleTextures.h"

ModuleSaveData::ModuleSaveData() : Module()
{
	savescore = 0;
}

ModuleSaveData::~ModuleSaveData()
{

}


bool ModuleSaveData::Init()
{

	Hud2 = App->textures->Load("Alphabet&Numbers&Extra.png");
	font_score = App->fonts->Load("fonts/Commando_font.png", "0123456789", 1);
	font_score2 = App->fonts->Load("fonts/Commando_font2.png", "0123456789", 1);
	return true;
}


update_status ModuleSaveData::Update()
{	
	if(savescore_p1 < App->UI->score)
	savescore_p1 = App->UI->score;
	if (savescore < App->UI -> score)
		savescore = App->UI -> score;
	return update_status::UPDATE_CONTINUE;
}

bool ModuleSaveData::CleanUp()
{
	App->textures->Unload(Hud2);
	App->fonts->UnLoad(font_score);
	App->fonts->UnLoad(font_score2);
	
	return true;
}


