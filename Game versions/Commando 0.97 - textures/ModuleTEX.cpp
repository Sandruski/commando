#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleTEX.h"

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

ModuleTEX::ModuleTEX() : Module()
{}

// Destructor
ModuleTEX::~ModuleTEX()
{}

// Called before render is available
bool ModuleTEX::Init()
{
	bool ret = true;

	A = App->textures->Load("Assets/Background/Secret_Rooms/1-1/Commando 1-A.png");
	B = App->textures->Load("Assets/Sprites/items&HUD&snake.png");

	C = App->textures->Load("Assets/Background/Secret_Rooms/1-1/salasecretea1-B.png");

	D = App->textures->Load("Assets/Background/Secret_Rooms/1-1/salasecretea1-C.png");
	E = App->textures->Load("Assets/Background/Secret_Rooms/1-1/salasecretea1-D.png");

	F = App->textures->Load("Assets/Background/Secret_Rooms/1-1/1-E.png");
	G = App->textures->Load("Assets/Sprites/Gun_PowerUp.png");

	helicopter = App->textures->Load("Assets/Sprites/helicopterfix.png");
	graphics2 = App->textures->Load("Assets/Background/1-1.png");
	playerhelicopter = App->textures->Load("Assets/Sprites/spritesheet_humanos.png");

	Gameover = App->textures->Load("Assets/Sprites/gameover.png");

	alphabet = App->textures->Load("Assets/Sprites/Alphabet&num.png");
	animation = App->textures->Load("Assets/Sprites/Endlevel1.png");


	sprites = App->textures->Load("Assets/Sprites/spritesheet_humanos.png");

	graphics = App->textures->Load("Assets/Background/menu.png");
	grenade = App->textures->Load("Assets/Sprites/items&HUD&snake.png");
	newmodetxt = App->textures->Load("Assets/Sprites/spritesheet_superjane.png");

	H = App->textures->Load("Assets/Sprites/particles.png");

	JANE = App->textures->Load("Assets/Sprites/spritesheet_superjane.png");
	Hud2 = App->textures->Load("Assets/Sprites/Alphabet&Numbers&Extra.png");



	moto1 = App->textures->Load("Assets/Sprites/vehicles.png");
	items1 = App->textures->Load("Assets/Sprites/items&HUD&snake.png");
	graphics1 = App->textures->Load("Assets/Background/1-1.png");
	win1 = App->textures->Load("Assets/Sprites/win.png");
	end_door1 = App->textures->Load("Assets/Sprites/door.png");


	Hud = App->textures->Load("Assets/Sprites/items&HUD&snake.png");

	Inv = App->textures->Load("Assets/Sprites/Invincible.png");


	return ret;
}

// Called before quitting
bool ModuleTEX::CleanUp()
{

	App->textures->Unload(Hud);
	App->textures->Unload(Inv);

	App->textures->Unload(moto1);
	App->textures->Unload(items1);
	App->textures->Unload(graphics1);
	App->textures->Unload(win1);

	App->textures->Unload(end_door1);






	App->textures->Unload(Hud2);
	App->textures->Unload(alphabet);
	App->textures->Unload(H);
	App->textures->Unload(animation);

	App->textures->Unload(JANE);

	App->textures->Unload(sprites);
	App->textures->Unload(graphics);
	App->textures->Unload(grenade);
	App->textures->Unload(newmodetxt);
	App->textures->Unload(graphics2);
	App->textures->Unload(helicopter);
	App->textures->Unload(playerhelicopter);

	App->textures->Unload(Gameover);

	App->textures->Unload(A);
	App->textures->Unload(B);
	App->textures->Unload(C);
	App->textures->Unload(D);
	App->textures->Unload(E);
	App->textures->Unload(F);
	App->textures->Unload(G);

	return true;
}