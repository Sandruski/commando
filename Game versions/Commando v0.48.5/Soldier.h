#ifndef __SOLDIER_H__
#define __SOLDIER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Soldier : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	Animation up_left, up_right, down_left, down_right, up, down, left, right;

	iPoint original_pos;
	fPoint save_step;
	Path path;
	int current_frame;

	//Shot
	fPoint enemyplayer, enemyplayeru;
	float module, angle;
	int rand1 = 3, num_shots, space = 0;

	//Movement
	fPoint enemyplayer2, enemyplayeru2;
	fPoint speed2 = { 0.0f, 0.0f };
	fPoint h = { 0.0f,0.0f };
	float module2;

public:

	Enemy_Soldier(int x, int y);

	void Move();
	void OnCollision(Collider* collider, Collider* c2);
};

#endif