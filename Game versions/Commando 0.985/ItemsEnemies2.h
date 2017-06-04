#ifndef __ITEMS_ENEMIES2_H__
#define __ITEMS_ENEMIES2_H__

#include "Enemy.h"

class ItemsEnemies2 : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	int original_y = 0;
	int original_x = 0;

	Animation drop1;

	int cont = 0;

public:

	ItemsEnemies2(int x, int y);

	void OnCollision(Collider* c1, Collider* c2);
};

#endif