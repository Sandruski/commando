#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticlesEnemies.h"
#include "ModulePlayer.h"
//#include "ModuleCollision.h"

#include "SDL/include/SDL_timer.h"

ModuleParticlesEnemies::ModuleParticlesEnemies()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticlesEnemies::~ModuleParticlesEnemies()
{}

// Load assets
bool ModuleParticlesEnemies::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("particles.png");


	bala.anim.PushBack({ 32, 16, 7, 7 });
	explosion.anim.PushBack({ 16,34,11,11 });
	bala.speed.y = -6;
	bala.life = 1300;
	return true;
}

// Unload assets
bool ModuleParticlesEnemies::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticlesEnemies::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle1* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;


			}
		}
	}

	return UPDATE_CONTINUE;
}


void ModuleParticlesEnemies::AddParticle(const Particle1& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle1* p = new Particle1(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x + 9;
			p->position.y = y - 15;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}


void ModuleParticlesEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			//AddParticle(explosion, active[i]->position.x, active[i]->position.y);
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}


// -------------------------------------------------------------
// -------------------------------------------------------------

Particle1::Particle1()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle1::Particle1(const Particle1& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle1::~Particle1()
{
	if (collider != nullptr)
		collider->to_delete = true;
}
bool Particle1::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	return ret;
}
