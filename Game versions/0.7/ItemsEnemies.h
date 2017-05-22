#ifndef __ITEMS_ENEMIES_H__
#define __ITEMS_ENEMIES_H__

#include "Enemy.h"

class ItemsEnemies : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	int original_y = 0;
	int original_x = 0;

	Animation drop2;

	int cont = 0;

public:

	ItemsEnemies(int x, int y);

	void OnCollision(Collider* c1, Collider* c2);
};

#endif