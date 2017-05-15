#ifndef __SOLDIER_GRENADE_H__
#define __SOLDIER_GRENADE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_SoldierGrenade : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	int original_y = 0;
	int original_x = 0;
	int cont = 0;

	Animation turn1, turn2, die;

public:

	Enemy_SoldierGrenade(int x, int y);
	void OnCollision(Collider* c1, Collider* c2);
	bool dieB = false;
	uint lastTime, currentTime;

	fPoint enemyplayer, enemyplayeru;
	float module, angle;
	int rand1 = 3, num_shots, space = 0;

	void Move();
};

#endif