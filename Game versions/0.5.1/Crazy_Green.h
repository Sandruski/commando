#ifndef __CRAZY_GREEN_H__
#define __CRAZY_GREEN_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_CrazyGreen : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	int original_y = 0;
	int original_x = 0;

	Animation run1, run2;
	Animation die;
	int cont = 0;

public:

	Enemy_CrazyGreen(int x, int y);

	void Move();
};

#endif