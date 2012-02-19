#ifndef _SOUNDS_H
#define _SOUNDS_H

#include "fmod.h"
#include "fmod.hpp"
#include <Windows.h>

class Sounds
{
private:
	FMOD::Sound* fireTowerAttack;
	FMOD::Sound* trollDeath;
	FMOD_RESULT result;
	FMOD::System* system;
	FMOD::Channel* Channel;
	FMOD::Channel* Channels[10];
public:
	Sounds();
	void initSounds();
	void PlaySounds(int _sound);
};

#endif;