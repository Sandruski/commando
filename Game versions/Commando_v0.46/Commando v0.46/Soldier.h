#ifndef __SOLDIER_H__
#define __SOLDIER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Soldier : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	int original_y = 0;
	int original_x = 0;

	Animation move;
	Animation die;

public:

	Enemy_Soldier(int x, int y);

	void Move();
};

#endif