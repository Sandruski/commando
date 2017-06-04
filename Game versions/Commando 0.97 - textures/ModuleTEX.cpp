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
	if (Hud != nullptr) 
		App->textures->Unload(Hud);

	if (Inv != nullptr)
	App->textures->Unload(Inv);

	if (moto1 != nullptr)
	App->textures->Unload(moto1);

	if (items1 != nullptr)
	App->textures->Unload(items1);

	if (graphics1 != nullptr)
	App->textures->Unload(graphics1);

	if (win1 != nullptr)
	App->textures->Unload(win1);

	if (end_door1 != nullptr)
	App->textures->Unload(end_door1);

	if (Hud2 != nullptr)
	App->textures->Unload(Hud2);

	if (alphabet != nullptr)
	App->textures->Unload(alphabet);

	if (H != nullptr)
	App->textures->Unload(H);

	if (animation != nullptr)
	App->textures->Unload(animation);

	if (JANE != nullptr)
	App->textures->Unload(JANE);

	if (sprites != nullptr)
	App->textures->Unload(sprites);

	if (graphics != nullptr)
	App->textures->Unload(graphics);

	if (grenade != nullptr)
	App->textures->Unload(grenade);

	if (newmodetxt != nullptr)
	App->textures->Unload(newmodetxt);

	if (graphics2 != nullptr)
	App->textures->Unload(graphics2);

	if (helicopter != nullptr)
	App->textures->Unload(helicopter);

	if (playerhelicopter != nullptr)
	App->textures->Unload(playerhelicopter);

	if (Gameover != nullptr)
	App->textures->Unload(Gameover);

	if (A != nullptr)
	App->textures->Unload(A);

	if (B != nullptr)
	App->textures->Unload(B);

	if (C != nullptr)
	App->textures->Unload(C);

	if (D != nullptr)
	App->textures->Unload(D);

	if (E != nullptr)
	App->textures->Unload(E);

	if (F != nullptr)
	App->textures->Unload(F);

	if (G != nullptr)
	App->textures->Unload(G);

	return true;
}