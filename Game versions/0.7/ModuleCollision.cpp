#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"


ModuleCollision::ModuleCollision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	//COLLIDER_PLAYER_GRENADE and COLLIDER_END_OF_BULLET must be 'false' ALWAYS!!!
	//COLLIDER_END_OF_GRENADE and COLLIDER_PLAYER_SHOT are the ones that kill enemies

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_WATER] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_FEET] = false;
	matrix[COLLIDER_WALL][COLLIDER_ITEM] = false;
	matrix[COLLIDER_WALL][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_GRENADE] = false;
	matrix[COLLIDER_WALL][COLLIDER_END_OF_BULLET] = false;
	matrix[COLLIDER_WALL][COLLIDER_END_OF_GRENADE] = false;
	matrix[COLLIDER_WALL][COLLIDER_SECRET_ROOM] = false;
	matrix[COLLIDER_WALL][COLLIDER_ITEM1] = false;
	matrix[COLLIDER_WALL][COLLIDER_FOLLOW] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_WALL][COLLIDER_REVIVE] = false;
	matrix[COLLIDER_WALL][COLLIDER_REVIVE2] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_WATER] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_FEET] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ITEM] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PRISONER] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_GRENADE] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_END_OF_BULLET] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_END_OF_GRENADE] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_SECRET_ROOM] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_ITEM1] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_FOLLOW] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_REVIVE] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_REVIVE2] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_REVIVE] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_REVIVE2] = true;

	matrix[COLLIDER_PLAYER2][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_WATER] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER_FEET] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_ITEM] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_PRISONER] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER_GRENADE] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_END_OF_BULLET] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_END_OF_GRENADE] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_REVIVE] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_REVIVE2] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_FOLLOW] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_SECRET_ROOM] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_WATER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_FEET] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ITEM] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_GRENADE] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_END_OF_BULLET] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_END_OF_GRENADE] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_SECRET_ROOM] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ITEM1] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_FOLLOW] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_REVIVE] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_REVIVE2] = false;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WATER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_FEET] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ITEM] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_GRENADE] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_END_OF_BULLET] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_END_OF_GRENADE] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_SECRET_ROOM] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ITEM1] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_FOLLOW] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_REVIVE] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_REVIVE2] = false;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WATER] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_FEET] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ITEM] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_GRENADE] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_END_OF_BULLET] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_END_OF_GRENADE] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_SECRET_ROOM] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ITEM1] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_FOLLOW] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_REVIVE] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_REVIVE2] = false;

	matrix[COLLIDER_WATER][COLLIDER_WALL] = false;
	matrix[COLLIDER_WATER][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WATER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WATER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_WATER][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_WATER][COLLIDER_WATER] = false;
	matrix[COLLIDER_WATER][COLLIDER_PLAYER_FEET] = false;
	matrix[COLLIDER_WATER][COLLIDER_ITEM] = false;
	matrix[COLLIDER_WATER][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_WATER][COLLIDER_PLAYER_GRENADE] = false;
	matrix[COLLIDER_WATER][COLLIDER_END_OF_BULLET] = false;
	matrix[COLLIDER_WATER][COLLIDER_END_OF_GRENADE] = false;
	matrix[COLLIDER_WATER][COLLIDER_SECRET_ROOM] = false;
	matrix[COLLIDER_WATER][COLLIDER_ITEM1] = false;
	matrix[COLLIDER_WATER][COLLIDER_FOLLOW] = false;
	matrix[COLLIDER_WATER][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_WATER][COLLIDER_REVIVE] = false;
	matrix[COLLIDER_WATER][COLLIDER_REVIVE2] = false;

	matrix[COLLIDER_PLAYER_FEET][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_WATER] = true;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_PLAYER_FEET] = true;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_ITEM] = true;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_PRISONER] = true;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_PLAYER_GRENADE] = false;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_END_OF_BULLET] = false;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_END_OF_GRENADE] = false;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_SECRET_ROOM] = true;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_ITEM1] = true;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_FOLLOW] = false;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_REVIVE] = false;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_REVIVE2] = false;

	matrix[COLLIDER_ITEM][COLLIDER_WALL] = false;
	matrix[COLLIDER_ITEM][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ITEM][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ITEM][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ITEM][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ITEM][COLLIDER_ITEM] = false;
	matrix[COLLIDER_ITEM][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_ITEM][COLLIDER_WATER] = false;
	matrix[COLLIDER_ITEM][COLLIDER_PLAYER_FEET] = true;
	matrix[COLLIDER_ITEM][COLLIDER_PLAYER_GRENADE] = false;
	matrix[COLLIDER_ITEM][COLLIDER_END_OF_BULLET] = false;
	matrix[COLLIDER_ITEM][COLLIDER_END_OF_GRENADE] = false;
	matrix[COLLIDER_ITEM][COLLIDER_SECRET_ROOM] = false;
	matrix[COLLIDER_ITEM][COLLIDER_ITEM1] = false;
	matrix[COLLIDER_ITEM][COLLIDER_FOLLOW] = false;
	matrix[COLLIDER_ITEM][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_ITEM][COLLIDER_REVIVE] = false;
	matrix[COLLIDER_ITEM][COLLIDER_REVIVE2] = false;

	matrix[COLLIDER_PLAYER_GRENADE][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER_GRENADE][COLLIDER_PLAYER_GRENADE] = false;
	matrix[COLLIDER_PLAYER_GRENADE][COLLIDER_PLAYER_FEET] = false;
	matrix[COLLIDER_PLAYER_GRENADE][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_PLAYER_GRENADE][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_GRENADE][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_PLAYER_GRENADE][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_GRENADE][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_GRENADE][COLLIDER_WATER] = false;
	matrix[COLLIDER_PLAYER_GRENADE][COLLIDER_ITEM] = false;
	matrix[COLLIDER_PLAYER_GRENADE][COLLIDER_END_OF_BULLET] = false;
	matrix[COLLIDER_PLAYER_GRENADE][COLLIDER_END_OF_GRENADE] = false;
	matrix[COLLIDER_PLAYER_GRENADE][COLLIDER_SECRET_ROOM] = false;
	matrix[COLLIDER_PLAYER_GRENADE][COLLIDER_ITEM1] = false;
	matrix[COLLIDER_PLAYER_GRENADE][COLLIDER_FOLLOW] = false;
	matrix[COLLIDER_PLAYER_GRENADE][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER_GRENADE][COLLIDER_REVIVE] = false;
	matrix[COLLIDER_PLAYER_GRENADE][COLLIDER_REVIVE2] = false;

	matrix[COLLIDER_END_OF_BULLET][COLLIDER_END_OF_GRENADE] = false;
	matrix[COLLIDER_END_OF_BULLET][COLLIDER_PLAYER_FEET] = false;
	matrix[COLLIDER_END_OF_BULLET][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_END_OF_BULLET][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_END_OF_BULLET][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_END_OF_BULLET][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_END_OF_BULLET][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_END_OF_BULLET][COLLIDER_WATER] = false;
	matrix[COLLIDER_END_OF_BULLET][COLLIDER_WALL] = false;
	matrix[COLLIDER_END_OF_BULLET][COLLIDER_ITEM] = false;
	matrix[COLLIDER_END_OF_BULLET][COLLIDER_PLAYER_GRENADE] = false;
	matrix[COLLIDER_END_OF_BULLET][COLLIDER_END_OF_BULLET] = false;
	matrix[COLLIDER_END_OF_BULLET][COLLIDER_SECRET_ROOM] = false;
	matrix[COLLIDER_END_OF_BULLET][COLLIDER_ITEM1] = false;
	matrix[COLLIDER_END_OF_BULLET][COLLIDER_FOLLOW] = false;
	matrix[COLLIDER_END_OF_BULLET][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_END_OF_BULLET][COLLIDER_REVIVE] = false;
	matrix[COLLIDER_END_OF_BULLET][COLLIDER_REVIVE2] = false;

	matrix[COLLIDER_END_OF_GRENADE][COLLIDER_END_OF_GRENADE] = false;
	matrix[COLLIDER_END_OF_GRENADE][COLLIDER_PLAYER_FEET] = false;
	matrix[COLLIDER_END_OF_GRENADE][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_END_OF_GRENADE][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_END_OF_GRENADE][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_END_OF_GRENADE][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_END_OF_GRENADE][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_END_OF_GRENADE][COLLIDER_WATER] = false;
	matrix[COLLIDER_END_OF_GRENADE][COLLIDER_WALL] = false;
	matrix[COLLIDER_END_OF_GRENADE][COLLIDER_ITEM] = false;
	matrix[COLLIDER_END_OF_GRENADE][COLLIDER_PLAYER_GRENADE] = false;
	matrix[COLLIDER_END_OF_GRENADE][COLLIDER_END_OF_BULLET] = false;
	matrix[COLLIDER_END_OF_GRENADE][COLLIDER_SECRET_ROOM] = true;
	matrix[COLLIDER_END_OF_GRENADE][COLLIDER_ITEM1] = false;
	matrix[COLLIDER_END_OF_GRENADE][COLLIDER_FOLLOW] = false;
	matrix[COLLIDER_END_OF_GRENADE][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_END_OF_GRENADE][COLLIDER_REVIVE] = false;
	matrix[COLLIDER_END_OF_GRENADE][COLLIDER_REVIVE2] = false;


	matrix[COLLIDER_PRISONER][COLLIDER_END_OF_GRENADE] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_PLAYER_FEET] = true;
	matrix[COLLIDER_PRISONER][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_PRISONER][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_WATER] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_WALL] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_ITEM] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_PLAYER_GRENADE] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_END_OF_BULLET] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_SECRET_ROOM] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_ITEM1] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_FOLLOW] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_PRISONER][COLLIDER_REVIVE] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_REVIVE2] = false;

	matrix[COLLIDER_REVIVE][COLLIDER_WALL] = false;
	matrix[COLLIDER_REVIVE][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_REVIVE][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_REVIVE][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_REVIVE][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_REVIVE][COLLIDER_WATER] = false;
	matrix[COLLIDER_REVIVE][COLLIDER_PLAYER_FEET] = false;
	matrix[COLLIDER_REVIVE][COLLIDER_ITEM] = false;
	matrix[COLLIDER_REVIVE][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_REVIVE][COLLIDER_PLAYER_GRENADE] = false;
	matrix[COLLIDER_REVIVE][COLLIDER_END_OF_BULLET] = false;
	matrix[COLLIDER_REVIVE][COLLIDER_END_OF_GRENADE] = false;
	matrix[COLLIDER_REVIVE][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_REVIVE][COLLIDER_REVIVE] = false;
	matrix[COLLIDER_REVIVE][COLLIDER_REVIVE2] = false;
	matrix[COLLIDER_REVIVE][COLLIDER_FOLLOW] = false;
	matrix[COLLIDER_REVIVE][COLLIDER_SECRET_ROOM] = false;

	matrix[COLLIDER_REVIVE2][COLLIDER_WALL] = false;
	matrix[COLLIDER_REVIVE2][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_REVIVE2][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_REVIVE2][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_REVIVE2][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_REVIVE2][COLLIDER_WATER] = false;
	matrix[COLLIDER_REVIVE2][COLLIDER_PLAYER_FEET] = false;
	matrix[COLLIDER_REVIVE2][COLLIDER_ITEM] = false;
	matrix[COLLIDER_REVIVE2][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_REVIVE2][COLLIDER_PLAYER_GRENADE] = false;
	matrix[COLLIDER_REVIVE2][COLLIDER_END_OF_BULLET] = false;
	matrix[COLLIDER_REVIVE2][COLLIDER_END_OF_GRENADE] = false;
	matrix[COLLIDER_REVIVE2][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_REVIVE2][COLLIDER_REVIVE2] = false;
	matrix[COLLIDER_REVIVE2][COLLIDER_FOLLOW] = false;
	matrix[COLLIDER_REVIVE2][COLLIDER_SECRET_ROOM] = false;

	matrix[COLLIDER_SECRET_ROOM][COLLIDER_END_OF_GRENADE] = true;
	matrix[COLLIDER_SECRET_ROOM][COLLIDER_PLAYER_FEET] = true;
	matrix[COLLIDER_SECRET_ROOM][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_SECRET_ROOM][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_SECRET_ROOM][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_SECRET_ROOM][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_SECRET_ROOM][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_SECRET_ROOM][COLLIDER_WATER] = false;
	matrix[COLLIDER_SECRET_ROOM][COLLIDER_WALL] = false;
	matrix[COLLIDER_SECRET_ROOM][COLLIDER_ITEM] = false;
	matrix[COLLIDER_SECRET_ROOM][COLLIDER_PLAYER_GRENADE] = false;
	matrix[COLLIDER_SECRET_ROOM][COLLIDER_END_OF_BULLET] = false;
	matrix[COLLIDER_SECRET_ROOM][COLLIDER_SECRET_ROOM] = false;
	matrix[COLLIDER_SECRET_ROOM][COLLIDER_ITEM1] = false;
	matrix[COLLIDER_SECRET_ROOM][COLLIDER_FOLLOW] = false;
	matrix[COLLIDER_SECRET_ROOM][COLLIDER_REVIVE] = false;
	matrix[COLLIDER_SECRET_ROOM][COLLIDER_REVIVE2] = false;
	matrix[COLLIDER_SECRET_ROOM][COLLIDER_FOLLOW] = false;

	matrix[COLLIDER_ITEM1][COLLIDER_WALL] = false;
	matrix[COLLIDER_ITEM1][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ITEM1][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ITEM1][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ITEM1][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ITEM1][COLLIDER_ITEM] = false;
	matrix[COLLIDER_ITEM1][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_ITEM1][COLLIDER_WATER] = false;
	matrix[COLLIDER_ITEM1][COLLIDER_PLAYER_FEET] = true;
	matrix[COLLIDER_ITEM1][COLLIDER_PLAYER_GRENADE] = false;
	matrix[COLLIDER_ITEM1][COLLIDER_END_OF_BULLET] = false;
	matrix[COLLIDER_ITEM1][COLLIDER_END_OF_GRENADE] = false;
	matrix[COLLIDER_ITEM1][COLLIDER_SECRET_ROOM] = false;
	matrix[COLLIDER_ITEM1][COLLIDER_ITEM1] = false;
	matrix[COLLIDER_ITEM1][COLLIDER_FOLLOW] = false;
	matrix[COLLIDER_ITEM1][COLLIDER_REVIVE] = false;
	matrix[COLLIDER_ITEM1][COLLIDER_REVIVE2] = false;
	matrix[COLLIDER_ITEM1][COLLIDER_FOLLOW] = false;

	matrix[COLLIDER_FOLLOW][COLLIDER_WALL] = false;
	matrix[COLLIDER_FOLLOW][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_FOLLOW][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_FOLLOW][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_FOLLOW][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_FOLLOW][COLLIDER_ITEM] = false;
	matrix[COLLIDER_FOLLOW][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_FOLLOW][COLLIDER_WATER] = false;
	matrix[COLLIDER_FOLLOW][COLLIDER_PLAYER_FEET] = false;
	matrix[COLLIDER_FOLLOW][COLLIDER_PLAYER_GRENADE] = false;
	matrix[COLLIDER_FOLLOW][COLLIDER_END_OF_BULLET] = false;
	matrix[COLLIDER_FOLLOW][COLLIDER_END_OF_GRENADE] = false;
	matrix[COLLIDER_FOLLOW][COLLIDER_SECRET_ROOM] = false;
	matrix[COLLIDER_FOLLOW][COLLIDER_ITEM1] = false;
	matrix[COLLIDER_FOLLOW][COLLIDER_FOLLOW] = true;
	matrix[COLLIDER_FOLLOW][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_FOLLOW][COLLIDER_REVIVE] = false;
	matrix[COLLIDER_FOLLOW][COLLIDER_REVIVE2] = false;
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_PLAYER2: // green
			App->render->DrawQuad(colliders[i]->rect, 50, 150, 50, alpha);
			break;
		case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_WATER: //orange
			App->render->DrawQuad(colliders[i]->rect, 255, 90, 0, alpha);
			break;
		case COLLIDER_PLAYER_FEET: //verd
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_ITEM: //black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case COLLIDER_PRISONER:
			App->render->DrawQuad(colliders[i]->rect, 100, 100, 100, alpha);
			break;
		case COLLIDER_PLAYER_GRENADE: //rainbowsinthesky
			App->render->DrawQuad(colliders[i]->rect, 23, 12, 3, alpha);
			break;
		case COLLIDER_END_OF_BULLET: //rainbowsinthesky
			App->render->DrawQuad(colliders[i]->rect, 23, 12, 3, alpha);
			break;
		case COLLIDER_END_OF_GRENADE: //YELLOW
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_SECRET_ROOM: 
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_ITEM1:
			App->render->DrawQuad(colliders[i]->rect, 15, 15, 255, alpha);
			break;
		case COLLIDER_FOLLOW:
			App->render->DrawQuad(colliders[i]->rect, 4, 30, 1, alpha);
			break;
		case COLLIDER_REVIVE: //rainbowsinthesky
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 100, alpha);
			break;
		case COLLIDER_REVIVE2: //rainbowsinthesky
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 100, alpha);
			break;
		}

	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

bool ModuleCollision::EraseCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w && rect.x + rect.w > r.x && rect.y < r.y + r.h && rect.h + rect.y > r.y);
}