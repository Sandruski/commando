#ifndef __GRENADES_B_H__
#define __GRENADES_B_H__

#include "Enemy.h"

class GrenadesB : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	int original_y = 0;
	int original_x = 0;

	Animation shine;
	int cont = 0;

public:

	GrenadesB(int x, int y);

	void OnCollision(Collider* c1, Collider* c2);
};

#endif