#ifndef __MODULEPARTICLESENEMIES_H__
#define __MODULEPARTICLESENEMIES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"


struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle1
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	fPoint position;
	fPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle1();
	Particle1(const Particle1& p);
	~Particle1();
	bool Update();
};

class ModuleParticlesEnemies : public Module
{
public:
	ModuleParticlesEnemies();
	~ModuleParticlesEnemies();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle1& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay);


private:
	SDL_Texture* graphics = nullptr;
	Particle1* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:
	Particle1 bala;
	Particle1 explosion;
};

#endif