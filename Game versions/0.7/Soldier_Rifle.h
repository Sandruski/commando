#ifndef __SOLDIER_RIFLE_H__
#define __SOLDIER_RIFLE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_SoldierRifle : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	int original_y = 0;
	int original_x = 0;

	Animation turn, center, left, more_left, right, more_right, die, invisible;
	Animation up;
	fPoint enemyplayer, enemyplayeru;
	float module, angle;


	int rand1 = 3, num_shots, space = 0;

public:

	uint lastTime, currentTime;
	bool dieB = false;
	Enemy_SoldierRifle(int x, int y);

	void OnCollision(Collider* c1, Collider* c2);
	void Move();

	int checking = 0, one = 0;

	int contador = 0;
};


#endif