#ifndef _ModuleAudio_H_
#define _ModuleAudio_H_

#include "Module.h"
#include "SDL_mixer/include/SDL_mixer.h"

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	bool play_music1();
	bool play_music2();
	bool play_music3();
	bool pause_music();

	bool play_fx1();

public:
	Mix_Music* music[MAX_MUSIC];
	Mix_Chunk* fx[MAX_FX];
};

#endif
