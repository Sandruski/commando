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

	Animation turn, die;

public:

	Enemy_SoldierGrenade(int x, int y);
	void OnCollision(Collider* c1);
	bool dieB = false;
	uint lastTime, currentTime;

	void Move();
};

#endif