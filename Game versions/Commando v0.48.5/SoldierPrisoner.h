#ifndef __SOLDIERPRISONER_H__
#define __SOLDIERPRISONER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_SoldierPrisoner : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	int original_y = 0;
	int original_x = 0;

	Animation movepoints;


public:

	int dieS;
	Enemy_SoldierPrisoner(int x, int y);
	void OnCollision(Collider* c1, Collider* c2);

	void Move();
};

#endif