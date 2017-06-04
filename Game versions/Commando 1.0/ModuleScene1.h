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
	

	//SDL_Texture* level = nullptr;
	Animation ammo_grenades_colours, ammo_specialgrenade1, door, moto_go, lvl1, win1, moto_stop, radio;
	SDL_Rect background, Secret_Room, r, reee, foreground;
	Animation* current_animation = nullptr;
	Animation* current_animation1 = nullptr;
	int cont5;
	int cont7;
	int contcamera2 = 0;
	int contcamera1 = 0;
	bool cont8 = false;
	bool cont6 = false;
	bool check = true;
	int w = 0, h = SCREEN_HEIGHT - 2880;
	int w_m = 255, h_m = 20;
	double long contador = 0;

	bool check_audio = true, check_audio1 = true, check_audio2 = true, check_audio3 = true;
	//Camera parameters
	int cont = 0, speed = 1;

	bool crazy = true;
	bool added = true;
	bool play_win = false;
	int tempo1 = 0;
	bool check_UI = true;
	bool winB = false;
	bool melasuda = false;

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

	bool yeee = false;

	void OnCollision(Collider* c1, Collider* c2);

	//Enemies drop items

	Animation drop1, drop2;
	SDL_Rect r1;
	bool torevivecheck1;
	bool torevivecheck2;
	bool torevivecheck3;
	bool torevivecheck4;

	int enemydiex, enemydiey;

	bool dead = false, first = true, first2 = true;

	int contenemy1 = 0, contenemy2 = 0, contenemy3 = 0, contenemy4 = 0, contenemy5 = 0;
	bool E1 = false, E2 = false, E3 = false, E4 = false, E5 = false;
	int spawn1 = 0, spawn2 = 0, spawn3 = 0, spawn4 = 0, spawn5 = 0, spawn6 = 0;
	bool B1 = false, B2 = false, B3 = false, B4 = false, B5 = false, B6 = false;
	bool TE = true;
};

#endif // __MODULESCENE1_H__