#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	void OnCollision(Collider* c1, Collider* c2);
	void OnCollisionWall(Collider* c1, Collider* c2);
	void OnCollisionItem(Collider* c1, Collider* c2);
	void OnCollisionWater(Collider* c1, Collider* c2);
	void OnCollisionEnemy(Collider* c1, Collider* c2);
	void OnCollisionRev(Collider* c1, Collider* c2);
	void Shot();

	update_status Update();
	bool CleanUp();

	Animation idleF;
	Animation forward, right, backward, left, diagWD, diagWA, diagSD, diagSA, invisible, grenade, die, waterDie;
	iPoint position;
	Animation* current_animation = &idleF;
	Collider* coll;
	Collider* collrev;
	Collider* feetC;
	Collider* grenadeC;
	SDL_Rect r, R;

	int vides = 3;
	bool move = true;
	bool move2 = true;
	bool waterB = true;
	bool enemyB = true;
	bool GOD = false;
	int speed;
	bool timeW = false;
	bool collW = false;
	bool collA = false;
	bool collS = false;
	bool collD = false;
	bool twoplayerson = false;
	bool granade = false;
	bool granadeUp = false;
	bool GunPowerUp = false;
	int SoldierPowerUp = 0;
	int randomsound;

	bool cooldown = false;
	uint lastTime, currentTime, allTime, finalTime;

	bool non_grenade = false;
	bool play_ending = false;
	iPoint p1, p2, p3, p4;
	int check_grenade = 1, check_nonshoot = 1, update_position_grenade = 0;
	bool playerdeadwaiting = false;
	//Save position where player died
	int save_player_position = 0;
	int revTime = 0;
	//Animation hpRev1, hpRev2, hpRev3, hpRev4;
	SDL_Rect  hpRev1, hpRev2, hpRev3, hpRev4;
	bool contdead = 0;
	bool detectionlive = 0;
	bool checkwaterdead = false;
	bool checkwaterdead2 = false;
	bool checkwaterdead3 = false;

	SDL_Rect torevive2;
	int torevive = 0;
};

#endif
