#pragma once

#include"fmod.h"
#include"fmod.hpp"
#include <cstdio>
class SoundManager
{
public:
	
	~SoundManager();

	static SoundManager& GetInstance();
	void DestroyInstance();

	void PlayerAttackSound();
	void PlayerJumpSound();
	void MonsterHitSound();
	void SoundUpdate();


	void Init();

private:
	SoundManager();
	SoundManager(const SoundManager& soundManager);
	SoundManager& operator=(const SoundManager& soundManager);

	FMOD::System     *system = 0;
	FMOD::Sound      *m_player_attack, *m_player_jump, *m_monster_hit;
	FMOD::Channel    *channel = 0;
	FMOD_RESULT       result;
	unsigned int      version;
	void             *extradriverdata = 0;


protected:

	static SoundManager* sm_pInstance;
};

