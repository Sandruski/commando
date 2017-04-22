#ifndef __PRISONERPOINTS_H__
#define __PRISONERPOINTS_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_PrisonerPoints : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	int original_y = 0;
	int original_x = 0;

	Animation movepoints;
	Animation move2;
	int cont;

public:

	Enemy_PrisonerPoints(int x, int y);

	void Move();
};

#endif