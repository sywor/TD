#ifndef _SOUNDS_H
#define _SOUNDS_H

#include "fmod.h"
#include "fmod.hpp"
#include "Timer.h"
#include <Windows.h>

class Sounds
{
private:
	FMOD::Sound* fireTowerAttack;
	FMOD::Sound* trollDeath;
	FMOD_RESULT result;	
	FMOD::Channel* Channel;

public:
	Sounds(FMOD::System* _system);
	Sounds();
	void initSounds();
	void PlaySounds(int _sound);
	FMOD::System* system;
	int channelIndex;
};

#endif;