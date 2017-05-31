#ifndef __MODULEPARTICLESGRENADE_H__
#define __MODULEPARTICLESGRENADE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"


struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle2
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle2();
	Particle2(const Particle2& p);
	~Particle2();
	bool Update();
};

class ModuleParticlesGrenade : public Module
{
public:
	ModuleParticlesGrenade();
	~ModuleParticlesGrenade();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle2& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay);


private:
	SDL_Texture* graphics = nullptr;
	Particle2* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:
	Particle2 grenade;
	Particle2 grenade2;
	Particle2 explosion;
};

#endif