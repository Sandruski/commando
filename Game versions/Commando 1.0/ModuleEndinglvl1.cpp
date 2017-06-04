#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleScene1.h"
#include "ModuleMenu.h"
#include "ModuleEnding.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleTEX.h"
#include "SDL/include/SDL.h"
#include "ModuleEND.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleParticlesEnemies.h"
#include "ModuleParticlesGrenade.h"
#include "ModuleParticlesGrenade1.h"
#include "ModuleParticles.h"
#include "ModuleCinematic.h"
#include "ModuleUI.h"
#include <windows.h>
#include "ModuleEndingLvl1.h"
#include "ModuleFonts.h" 
#include "ModuleSaveData.h"

#include<stdio.h>
#include<string.h>


ModuleEndingLvl1::ModuleEndingLvl1()
{
	//guy animation
	guy.PushBack({ 1, 0, 36, 64 });
	guy.PushBack({ 37, 0, 36, 64 });
	guy.PushBack({ 73, 0, 36, 64 });
	guy.PushBack({ 1, 0, 36, 64 });
	guy.PushBack({ 37, 0, 36, 64 });
	guy.PushBack({ 73, 0, 36, 64 });
	guy.PushBack({ 1, 0, 36, 64 });
	guy.PushBack({ 37, 0, 36, 64 });
	guy.PushBack({ 73, 0, 36, 64 });
	guy.PushBack({ 1, 0, 36, 64 });
	guy.PushBack({ 37, 0, 36, 64 });
	guy.loop = false;
	guy.speed = 0.02f;

	//A
	a.x = 1;
	a.y = 11;
	a.w = 8;
	a.h = 8;
	//B
	b.x = 19;
	b.y = 11;
	b.w = 8;
	b.h = 8;
	//C
	c.x = 28;
	c.y = 11;
	c.w = 8;
	c.h = 8;
	//D
	d.x = 39;
	d.y = 11;
	d.w = 8;
	d.h = 8;
	//E
	e.x = 56;
	e.y = 11;
	e.w = 8;
	e.h = 8;
	//F
	f.x = 67;
	f.y = 11;
	f.w = 8;
	f.h = 8;
	//G
	g.x = 77;
	g.y = 11;
	g.w = 8;
	g.h = 8;
	//H
	h.x = 88;
	h.y = 11;
	h.w = 8;
	h.h = 8;
	//I
	i.x = 10;
	i.y = 20;
	i.w = 8;
	i.h = 8;
	//L
	l.x = 49;
	l.y = 20;
	l.w = 7;
	l.h = 8;
	//K
	k.x = 39;
	k.y = 20;
	k.w = 8;
	k.h = 8;
	//M
	m.x = 58;
	m.y = 20;
	m.w = 8;
	m.h = 8;
	//N
	n.x = 68;
	n.y = 20;
	n.w = 8;
	n.h = 8;
	//O
	o.x = 78;
	o.y = 20;
	o.w = 8;
	o.h = 8;
	//P
	p.x = 87;
	p.y = 20;
	p.w = 8;
	p.h = 8;
	//R
	r.x = 1;
	r.y = 29;
	r.w = 8;
	r.h = 8;
	//S
	s.x = 11;
	s.y = 29;
	s.w = 8;
	s.h = 8;
	//T
	t.x = 20;
	t.y = 29;
	t.w = 7;
	t.h = 8;
	//U
	u.x = 29;
	u.y = 29;
	u.w = 8;
	u.h = 8;
	//W
	w.x = 49;
	w.y = 29;
	w.w = 8;
	w.h = 8;



	//// zero

	//// one
	one.x = 9;
	one.y = 1;
	one.w = 8;
	one.h = 8;
	// two
	two.x = 18;
	two.y = 1;
	two.w = 8;
	two.h = 8;


	//pone
	pone.x = 35;
	pone.y = 39;
	pone.w = 22;
	pone.h = 8;


	//highsc
	highsc.x = 2;
	highsc.y = 39;
	highsc.w = 32;
	highsc.h = 8;

}

ModuleEndingLvl1::~ModuleEndingLvl1()
{}

// Load assets
bool ModuleEndingLvl1::Start()
{
	time = 0;
	contador = 0;

	App->audio->play_music9();


	LOG("Loading endlvl scene");
	bool ret = true;
	App->render->camera.x = App->render->camera.y = 0;


	return ret;
}

// UnLoad assets
bool ModuleEndingLvl1::CleanUp()
{
	return true;
}

// Update: draw background
update_status ModuleEndingLvl1::Update()
{

	App->render->Blit(App->TEX->alphabet, 110, 19 - (App->render->camera.y / 3), &highsc);// hsc
	App->render->Blit(App->TEX->alphabet, 20, 19 - (App->render->camera.y / 3), &pone);// pone

	contador++;
	time += 0.02f;

	if (contador == 400) {
		App->audio->pause_music();
	}

	// Draw everything --------------------------------------
	App->render->Blit(App->TEX->animation, 104, 105, &(guy.GetCurrentFrame()), 1.0f); // guy animation

	sprintf_s(App->UI->str1, "%i", App->savedata->savescore_p1);
	App->fonts->BlitText(18, 27, App->savedata->font_score, App->UI->str1);

	sprintf_s(App->UI->str2, "%i", App->savedata->savescore);
	App->fonts->BlitText(104, 27, App->savedata->font_score2, App->UI->str2);


	if (time>1)
		App->render->Blit(App->TEX->alphabet, 32, 40, &b);
	if (time > 1.2)
		App->render->Blit(App->TEX->alphabet, 40, 40, &r);
	if (time > 1.4)
		App->render->Blit(App->TEX->alphabet, 48, 40, &o);
	if (time > 1.6)
		App->render->Blit(App->TEX->alphabet, 56, 40, &k);
	if (time > 1.8)
		App->render->Blit(App->TEX->alphabet, 64, 40, &e);

	if (time > 2)
		App->render->Blit(App->TEX->alphabet, 81, 40, &t);
	if (time > 2.2)
		App->render->Blit(App->TEX->alphabet, 88, 40, &h);
	if (time > 2.4)
		App->render->Blit(App->TEX->alphabet, 96, 40, &e);

	if (time>2.6)
		App->render->Blit(App->TEX->alphabet, 112, 40, &one);
	if (time > 2.8)
		App->render->Blit(App->TEX->alphabet, 120, 40, &s);
	if (time > 3)
		App->render->Blit(App->TEX->alphabet, 128, 40, &t);


	if (time > 3.2)
		App->render->Blit(App->TEX->alphabet, 144, 40, &a);
	if (time > 3.4)
		App->render->Blit(App->TEX->alphabet, 152, 40, &r);
	if (time > 3.6)
		App->render->Blit(App->TEX->alphabet, 160, 40, &e);
	if (time > 3.8)
		App->render->Blit(App->TEX->alphabet, 168, 40, &a);

	if (time>4)
		App->render->Blit(App->TEX->alphabet, 32, 56, &n);
	if (time > 4.2)
		App->render->Blit(App->TEX->alphabet, 40, 56, &o);
	if (time > 4.4)
		App->render->Blit(App->TEX->alphabet, 48, 56, &w);

	if (time>4.6)
		App->render->Blit(App->TEX->alphabet, 64, 56, &r);
	if (time > 4.8)
		App->render->Blit(App->TEX->alphabet, 72, 56, &u);
	if (time > 5)
		App->render->Blit(App->TEX->alphabet, 80, 56, &s);
	if (time > 5.2)
		App->render->Blit(App->TEX->alphabet, 88, 56, &h);

	if (time > 5.4)
		App->render->Blit(App->TEX->alphabet, 105, 56, &t);
	if (time > 5.6)
		App->render->Blit(App->TEX->alphabet, 112, 56, &o);

	if (time > 5.8)
		App->render->Blit(App->TEX->alphabet, 129, 56, &t);
	if (time > 6)
		App->render->Blit(App->TEX->alphabet, 136, 56, &h);
	if (time > 6.2)
		App->render->Blit(App->TEX->alphabet, 143, 56, &e);

	if (time>6.4)
		App->render->Blit(App->TEX->alphabet, 160, 56, &two);
	if (time > 6.6)
		App->render->Blit(App->TEX->alphabet, 168, 56, &n);
	if (time > 6.8)
		App->render->Blit(App->TEX->alphabet, 176, 56, &d);

	if (time > 7)
		App->render->Blit(App->TEX->alphabet, 192, 56, &a);
	if (time > 7.2)
		App->render->Blit(App->TEX->alphabet, 200, 56, &r);
	if (time > 7.4)
		App->render->Blit(App->TEX->alphabet, 208, 56, &e);
	if (time > 7.6)
		App->render->Blit(App->TEX->alphabet, 216, 56, &a);

	if (time>12) {
		App->fade->FadeToBlack(this, App->Menu);
	}

	return UPDATE_CONTINUE;
}