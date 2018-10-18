#include "SoundManager.h"

#include "fmod.h"
#include "fmod.hpp"
#include <cstdio>



SoundManager* SoundManager::sm_pInstance = 0;

SoundManager&
SoundManager::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new SoundManager();
	}

	return (*sm_pInstance);
}

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
	result = system->close();
	result = system->release();
}

void
SoundManager::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;

	SoundManager::~SoundManager();
}

void SoundManager::PlayerAttackSound()
{
	result = system->playSound(m_player_attack, 0, false, &channel);

}

void SoundManager::MonsterHitSound()
{
	result = system->playSound(m_monster_hit, 0, false, &channel);

}

void SoundManager::PlayerJumpSound()
{
	result = system->playSound(m_player_jump, 0, false, &channel);
}

void SoundManager::SoundUpdate()
{
	system->update();
}

void SoundManager::Init()
{

	//inisliseing sound wiht fmod
	result = FMOD::System_Create(&system);      // Create the main system object.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, "fmod error");	
	}

	result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, "fmod error");	
	}
	result = system->createSound("assets\\game_sound\\player_attack.wav", FMOD_CREATESAMPLE, 0, &m_player_attack);
	result = system->createSound("assets\\game_sound\\player_jump.wav", FMOD_CREATESAMPLE, 0, &m_player_jump);
	result = system->createSound("assets\\game_sound\\monster_hit.wav", FMOD_CREATESAMPLE, 0, &m_monster_hit);

}





