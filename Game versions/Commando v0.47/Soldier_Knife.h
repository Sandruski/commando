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

	Animation up, down, right, left;
	iPoint original_pos;
	int cont = 0;

public:

	Enemy_SoldierKnife(int x, int y);
	Path path, path1;
	void Move();
};

#endif