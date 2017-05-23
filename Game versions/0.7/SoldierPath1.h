#ifndef __SOLDIER_PATH1_H__
#define __SOLDIER_PATH1_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Soldier1 : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	Animation die, up_left, up_right, down_left, down_right, up, down, left, right;

	fPoint original_pos;
	fPoint save_step;
	Path pathA, pathB;
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

	fPoint i = { -1.0f, -1.0f };

public:

	Enemy_Soldier1(int x, int y);

	void Move();
	uint lastTime, currentTime;
	bool dieB = false;
	bool collW = false, collA = false, collS = false, collD = false;
	void OnCollision(Collider* c1, Collider* c2);

	bool hi = false;
	bool one = true, two = true, three = true;

	bool anim1, anim2;
	fPoint another;
	bool yeah = true;
	bool NO1 = false, NO2 = false, NO3 = false, NO4 = false;
	int NO_CONT = 0;

	bool dont_move = true;
};

#endif