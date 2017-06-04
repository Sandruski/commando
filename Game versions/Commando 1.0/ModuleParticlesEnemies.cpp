#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticlesEnemies.h"
#include "ModuleTEX.h"
#include "ModulePlayer.h"
//#include "ModuleCollision.h"

#include "SDL/include/SDL_timer.h"

ModuleParticlesEnemies::ModuleParticlesEnemies()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	grenade.anim.PushBack({ 126, 16, 5, 6 });
	grenade.anim.PushBack({ 139, 16, 5, 6 });
	grenade.anim.PushBack({ 126, 16, 5, 6 });
	grenade.anim.PushBack({ 139, 16, 5, 6 });
	grenade.anim.PushBack({ 126, 16, 5, 6 });
	grenade.anim.PushBack({ 139, 16, 5, 6 });
	grenade.anim.speed = 0.1f;
	grenade.speed.y = -6;
	grenade.life = 1500;

	explosiongrenade.anim.PushBack({ 24, 117, 15, 14 });
	explosiongrenade.anim.PushBack({ 62, 112, 25, 24 });
	explosiongrenade.anim.speed = 0.07f;
	explosiongrenade.anim.loop = false;

	bala.anim.PushBack({ 32, 16, 7, 7 });

	explosion.anim.PushBack({ 16,34,11,11 });
	explosion.life = 300;

	bala.speed.y = -6;
	bala.life = 1500;
}

ModuleParticlesEnemies::~ModuleParticlesEnemies()
{}

// Load assets
bool ModuleParticlesEnemies::Start()
{
	LOG("Loading particles");

	return true;
}

// Unload assets
bool ModuleParticlesEnemies::CleanUp()
{
	LOG("Unloading particles");

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
			App->render->Blit(App->TEX->H, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;


			}
		}
	}

	return UPDATE_CONTINUE;
}


void ModuleParticlesEnemies::AddParticle(const Particle1& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay, fPoint speed)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle1* p = new Particle1(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x /*+ 9*/;
			p->position.y = y /*- 15*/;
			p->speed.x = speed.x;
			p->speed.y = speed.y;
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
			App->particlesenemies->AddParticle(App->particlesenemies->explosion, active[i]->position.x, active[i]->position.y, COLLIDER_END_OF_BULLET, NULL, App->particlesenemies->explosion.speed);
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
		if ((SDL_GetTicks() - born) > life) {
			if (collider->type == COLLIDER_ENEMY_SHOT)
			{
				App->particlesenemies->AddParticle(App->particlesenemies->explosion, position.x, position.y, COLLIDER_END_OF_BULLET, NULL, App->particlesenemies->explosion.speed);
			}
			if (collider->type == COLLIDER_PLAYER_GRENADE)
			{
				App->particlesenemies->AddParticle(App->particlesenemies->explosiongrenade, position.x, position.y, COLLIDER_ENEMY_SHOT, NULL, App->particlesenemies->explosiongrenade.speed);
			}


			ret = false;
		}
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