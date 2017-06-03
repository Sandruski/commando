#ifndef __CRAZY_GREEN_H__
#define __CRAZY_GREEN_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_CrazyGreen : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	Path path;


	fPoint original_pos;
	fPoint save_step;
	Animation left, right;
	Animation die;
	int cont = 0;

public:
	
	uint lastTime, currentTime;
	bool dieB = false;

	Enemy_CrazyGreen(int x, int y);
	void OnCollision(Collider* c1, Collider* c2);
	void Move();
};

#endif