#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"


ModuleCollision::ModuleCollision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;


	matrix[COLLIDER_WALL][COLLIDER_WALL] = 0;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = 2;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = 2;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = 1;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = 1;
	matrix[COLLIDER_WALL][COLLIDER_WATER] = 0;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_FEET] = 0;
	matrix[COLLIDER_WALL][COLLIDER_ITEM] = 0;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = 2;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = 0;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = 1;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = 0;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = 1;
	matrix[COLLIDER_PLAYER][COLLIDER_WATER] = 1;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_FEET] = 0;
	matrix[COLLIDER_PLAYER][COLLIDER_ITEM] = 0;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = 2;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = 1;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = 0;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = 1;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = 0;
	matrix[COLLIDER_ENEMY][COLLIDER_WATER] = 1;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_FEET] = 0;
	matrix[COLLIDER_ENEMY][COLLIDER_ITEM] = 0;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = 1;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = 0;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = 1;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = 0;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = 0;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WATER] = 0;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_FEET] = 0;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ITEM] = 0;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = 1;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = 1;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = 0;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = 0;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = 0;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WATER] = 0;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_FEET] = 0;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ITEM] = 0;

	matrix[COLLIDER_WATER][COLLIDER_WALL] = 0;
	matrix[COLLIDER_WATER][COLLIDER_PLAYER] = 1;
	matrix[COLLIDER_WATER][COLLIDER_ENEMY] = 1;
	matrix[COLLIDER_WATER][COLLIDER_PLAYER_SHOT] = 0;
	matrix[COLLIDER_WATER][COLLIDER_ENEMY_SHOT] = 0;
	matrix[COLLIDER_WATER][COLLIDER_PLAYER_FEET] = 0;
	matrix[COLLIDER_WATER][COLLIDER_ITEM] = 0;

	matrix[COLLIDER_PLAYER_FEET][COLLIDER_WALL] = 2;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_PLAYER] = 0;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_ENEMY] = 1;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_PLAYER_SHOT] = 0;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_ENEMY_SHOT] = 1;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_WATER] = 1;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_ITEM] = 3;

	matrix[COLLIDER_ITEM][COLLIDER_WALL] = 0;
	matrix[COLLIDER_ITEM][COLLIDER_PLAYER] = 0;
	matrix[COLLIDER_ITEM][COLLIDER_ENEMY] = 0;
	matrix[COLLIDER_ITEM][COLLIDER_PLAYER_SHOT] = 0;
	matrix[COLLIDER_ITEM][COLLIDER_ENEMY_SHOT] = 0;
	matrix[COLLIDER_ITEM][COLLIDER_WATER] = 0;
	matrix[COLLIDER_ITEM][COLLIDER_PLAYER_FEET] = 3;
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
				if (matrix[c1->type][c2->type] == 2)
					c1->callback->OnCollisionWall();

				else if (matrix[c1->type][c2->type] == 3)
					c1->callback->OnCollisionItem(c1, c2);
				
				else if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				else if (matrix[c2->type][c1->type] && c2->callback)
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
		case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_WATER: //negre
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case COLLIDER_PLAYER_FEET: //verd
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_ITEM: //gris
			App->render->DrawQuad(colliders[i]->rect, 200, 200, 200, alpha);
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