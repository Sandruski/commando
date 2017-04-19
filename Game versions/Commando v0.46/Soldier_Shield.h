#ifndef __SOLDIER_SHIELD_H__
#define __SOLDIER_SHIELD_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_SoldierShield : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	int original_y = 0;
	int original_x = 0;

	Animation move;
	Animation surrender;

public:

	Enemy_SoldierShield(int x, int y);

	void Move();
};

#endif