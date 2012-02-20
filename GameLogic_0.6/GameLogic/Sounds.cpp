#include "Sounds.h"

Sounds::Sounds(FMOD::System* _system)
{
	system = _system;
	fireTowerAttack = NULL;
	trollDeath = NULL;
	Channel = 0;
	system = NULL;
	result = FMOD::System_Create(&system);
	system->setOutput(FMOD_OUTPUTTYPE_WASAPI);
	system->init(1024, FMOD_INIT_NORMAL, 0);
}

Sounds::Sounds()
{
	system = 0;
	fireTowerAttack = NULL;
	trollDeath = NULL;
	Channel = 0;
	system = NULL;
	result = FMOD::System_Create(&system);
	system->setOutput(FMOD_OUTPUTTYPE_WASAPI);
	system->init(1024, FMOD_INIT_NORMAL, 0);
	channelIndex = 0;
}

enum soundSelector
{
	ATTACK_FIRE = 0,
	DEATH_TROLL = 1
};

void Sounds::initSounds()
{
	result = system->createSound("FireTower_attack.mp3", 0, NULL, &fireTowerAttack);
	result = system->createSound("TrollMob_Death.wav", 0, NULL, &trollDeath);
}

void Sounds::PlaySounds(int _sound)
{
	switch(_sound)
	{
	case ATTACK_FIRE:
		result = system->playSound(FMOD_CHANNEL_FREE, fireTowerAttack, false, &Channel);
		break;
	case DEATH_TROLL:
		result = system->playSound(FMOD_CHANNEL_FREE, trollDeath, false, &Channel);
		break;
	}	
}