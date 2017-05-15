#ifndef __MODULESCENE1_H__
#define __MODULESCENE1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleScene1 : public Module
{
public:
	ModuleScene1();
	~ModuleScene1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Texture* moto = nullptr;
	SDL_Texture* items = nullptr;
	SDL_Texture* win = nullptr;
	//SDL_Texture* level = nullptr;
	SDL_Rect foreground;
	Animation ammo_grenades_colours;
	Animation ammo_specialgrenade1;
	Animation moto_go;
	Animation lvl1;
	Animation win1;
	Animation moto_stop;
	SDL_Rect background;
	SDL_Rect Secret_Room;
	SDL_Rect r;
	Animation* current_animation = nullptr;
	int cont5;
	int cont7;

	bool cont8 = false;
	bool cont6 = false;
	bool check = true;
	int w = 0, h = SCREEN_HEIGHT - 2880;
	int w_m = 255, h_m = 20;
	double long contador = 0;

	bool check_audio = true, check_audio1 = true, check_audio2 = true, check_audio3 = true;
	//Camera parameters
	int cont = 0, speed = 3;

	bool play_win = false;
	int tempo1 = 0;
	bool check_UI = true;
	bool winB = false;

	//Starting y positions of the player (for respawns)
	bool start = true; //initial position (when player appears for the first time) -> 110
	bool start1 = false; //2778 - 2656
	bool start2 = false; //2294 - 2656
	bool start3 = false; //1836 - 2656
	bool start4 = false; //882 - 2656
	bool start5 = false; //395 - 2656

	//Secret rooms
	bool roomA = false;
	bool roomB = false;
	bool roomC = false;
	bool roomD = false;
	bool roomE = false;
	int current_start_pos = 0;

	void OnCollision(Collider* c1, Collider* c2);

	//Enemies drop items
	bool blit_item = false;
	Animation drop1, drop2;
	SDL_Rect r1;
	Animation* current_animation1 = nullptr;
	int enemydiex, enemydiey;
	bool hello1 = true, hello2 = true, hello3 = true, hello4 = true, hello5 = true, hello6 = true;
};




#endif // __MODULESCENE1_H__