#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticlesGrenade.h"
#include "ModuleTEX.h"
#include "ModulePlayer.h"
//#include "ModuleCollision.h"

#include "SDL/include/SDL_timer.h"

ModuleParticlesGrenade::ModuleParticlesGrenade()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	grenade.anim.PushBack({ 126, 16, 5, 6 });
	grenade.anim.PushBack({ 139, 16, 5, 6 });
	grenade.anim.speed = 0.04;

	grenade2.anim.PushBack({ 126, 24, 5, 6 });
	grenade2.anim.PushBack({ 139, 24, 5, 6 });
	grenade2.anim.speed = 0.04;

	explosion.anim.PushBack({ 22, 115, 20, 20 });
	explosion.anim.PushBack({ 62, 112, 25, 24 });
}

ModuleParticlesGrenade::~ModuleParticlesGrenade()
{}

// Load assets
bool ModuleParticlesGrenade::Start()
{
	LOG("Loading particles");

	grenade.life = 900;
	grenade2.life = 900;

	return true;
}

// Unload assets
bool ModuleParticlesGrenade::CleanUp()
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
update_status ModuleParticlesGrenade::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle2* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			if (p->position.y <= 1405 - 2656 && p->position.y >= 1338 - 2656) {}

			else {
				App->render->Blit(App->TEX->H, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			}
			if (p->fx_played == false)
			{
				p->fx_played = true;

			}
		}
	}

	return UPDATE_CONTINUE;
}


void ModuleParticlesGrenade::AddParticle(const Particle2& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle2* p = new Particle2(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x + 9;
			p->position.y = y + 7;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}


void ModuleParticlesGrenade::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}


// -------------------------------------------------------------
// -------------------------------------------------------------

Particle2::Particle2()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle2::Particle2(const Particle2& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle2::~Particle2()
{
	if (collider != nullptr)
		collider->to_delete = true;
}
bool Particle2::Update()
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
