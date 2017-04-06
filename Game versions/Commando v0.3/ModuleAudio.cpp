#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "Module.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScene1.h"
#include "ModuleScene2.h"
#include "ModuleEND.h"
#include "ModuleMenu.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"

#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleAudio::ModuleAudio() {}

bool ModuleAudio::Init() {

	Mix_Init(MIX_INIT_OGG);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	//Load music
	music[0] = Mix_LoadMUS("Commando_Sound-01-Title.ogg");
	music[1] = Mix_LoadMUS("Commando_Sound-03-Areas_1-2-3.ogg");
	music[2] = Mix_LoadMUS("Commando_Sound-03-Areas_1-2-3.ogg");

	//Load FX
	fx[0] = Mix_LoadWAV("Commando_Effect-02-Principal-Shoot.wav");
	
	return true;
}

bool ModuleAudio::play_music1() {
	//Mix_PlayMusic(music[0], -1); play music without fade in
	Mix_FadeInMusic(music[0], -1, 2000);
	return true;
}
bool ModuleAudio::play_music2() {
	Mix_FadeInMusic(music[1], -1, 2000);
	return true;
}
bool ModuleAudio::play_music3() {
	Mix_FadeInMusic(music[2], -1, 2000);
	return true;
}
bool ModuleAudio::pause_music() {
	//Mix_PauseMusic(); pause music without fade out
	Mix_FadeOutMusic(2000);
	return true;
}
bool ModuleAudio::play_fx1() {
	Mix_PlayChannel(-1, fx[0], 1);
	return true;
}

bool ModuleAudio::CleanUp() {

	for (int i = 0; i < MAX_MUSIC; i++)
		Mix_FreeMusic(music[i]);

	for (int i = 0; i < MAX_FX; i++)
		Mix_FreeChunk(fx[i]);

	return true;
}

ModuleAudio::~ModuleAudio() {}