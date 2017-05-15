#ifndef __MODULEPARTICLESGRENADE1_H__
#define __MODULEPARTICLESGRENADE1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"


struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle3
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;



	Particle3();
	Particle3(const Particle3& p);
	~Particle3();
	bool Update();
};

class ModuleParticlesGrenade1 : public Module
{
public:
	ModuleParticlesGrenade1();
	~ModuleParticlesGrenade1();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle3& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay);


private:
	SDL_Texture* graphics = nullptr;
	Particle3* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:
	Particle3 grenade;
	Particle3 explosion;
};

#endif