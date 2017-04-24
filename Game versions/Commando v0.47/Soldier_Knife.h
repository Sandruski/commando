#ifndef __SOLDIER_KNIFE_H__
#define __SOLDIER_KNIFE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_SoldierKnife : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	int original_y = 0;
	int original_x = 0;

	Animation turn;

public:

	int original_posx;
	Enemy_SoldierKnife(int x, int y);
	Path path;
	void Move();
};

#endif