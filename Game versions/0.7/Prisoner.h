#ifndef __PRISONER_H__
#define __PRISONER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Prisoner : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	int original_y = 0;
	int original_x = 0;
	int cont = 0;

	Animation stand1, stand2;
	Animation run;
	Animation animated;

public:
	bool move = false;
	Enemy_Prisoner(int x, int y);
	void OnCollision(Collider* c1, Collider* c2);
	void Move();
};

#endif