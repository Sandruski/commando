#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticlesGrenade1.h"
#include "ModulePlayer.h"
//#include "ModuleCollision.h"

#include "SDL/include/SDL_timer.h"

ModuleParticlesGrenade1::ModuleParticlesGrenade1()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	grenade.anim.PushBack({ 126, 16, 5, 6 });
	grenade.anim.PushBack({ 139, 16, 5, 6 });
	grenade.anim.speed = 0.1;

	explosion.anim.PushBack({ 24, 117, 15, 14 });
	explosion.anim.PushBack({ 62, 112, 25, 24 });
	explosion.anim.speed = 0.07;
	

}

ModuleParticlesGrenade1::~ModuleParticlesGrenade1()
{}

// Load assets
bool ModuleParticlesGrenade1::Start()
{
	LOG("Loading particles");

	explosion.anim.loop = false;
	explosion.anim.speed = 0.1f;

	grenade.life = 300;
	explosion.life = 450;

	graphics = App->textures->Load("Assets/Sprites/particles.png");

	return true;
}

// Unload assets
bool ModuleParticlesGrenade1::CleanUp()
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
update_status ModuleParticlesGrenade1::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle3* p = active[i];

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
				App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			}
			if (p->fx_played == false)
			{
				p->fx_played = true;


			}
		}



	}

	return UPDATE_CONTINUE;
}


void ModuleParticlesGrenade1::AddParticle(const Particle3& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle3* p = new Particle3(particle);
			p->born = SDL_GetTicks() + delay;
			if (collider_type == COLLIDER_PLAYER_GRENADE) {
				p->position.x = x + 9;
				p->position.y = y + 7;
			}
			else if (collider_type == COLLIDER_END_OF_GRENADE) {
				p->position.x = x - 8;
				p->position.y = y;
			}
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}


void ModuleParticlesGrenade1::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			App->particlesgrenade1->AddParticle(App->particlesgrenade1->explosion, active[i]->position.x, active[i]->position.y, COLLIDER_END_OF_GRENADE, NULL);
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}


// -------------------------------------------------------------
// -------------------------------------------------------------

Particle3::Particle3()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle3::Particle3(const Particle3& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle3::~Particle3()
{
	if (collider != nullptr)
		collider->to_delete = true;
}
bool Particle3::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life) {
			if (collider->type == COLLIDER_PLAYER_GRENADE)
			{
				App->particlesgrenade1->AddParticle(App->particlesgrenade1->explosion, position.x, position.y, COLLIDER_END_OF_GRENADE, NULL);
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
