#include "Objectpools.h"





Objectpools::Objectpools()
	: MAX_ENEMY_SIZE(0)
	, CULTIST_HP(10)
	, m_active(false)
	, m_enemySpawnX(0)
	, m_enemySpawnY(4)
{
}


Objectpools::~Objectpools()
{
	for (int i = 0; i < MAX_ENEMY_SIZE; )
	{
		delete m_enemyPool[i];
		m_enemyPool[i] = 0;
		++i;
	}

	delete[] m_enemyPool;
	m_enemyPool = 0;
}

bool
Objectpools::Initialise(b2World* world, AnimatedSprite* sprite)
{
	MAX_ENEMY_SIZE = 20;
	m_enemyPool = new Enemy*[MAX_ENEMY_SIZE];

	for (int i = 0; i < MAX_ENEMY_SIZE; ++i)
	{
		m_enemySpawnX = (rand() % 20) + 2;
		m_enemyPool[i] = new Enemy(CULTIST_HP, FixtureType::ENEMY, m_enemySpawnX, m_enemySpawnY);
		m_enemyPool[i]->SetDead(m_active);
		m_enemyPool[i]->Initialise(world, sprite);
	}

	return (true);
}



void
Objectpools::Draw(BackBuffer* backBuffer)
{
	for (int i = 0; i < MAX_ENEMY_SIZE; ++i)
	{
		if (!m_enemyPool[i]->IsDead())
		{
			m_enemyPool[i]->Draw(backBuffer);
		}
	}
}

void
Objectpools::Process(float deltatime)
{
	for (int i = 0; i < MAX_ENEMY_SIZE; ++i)
	{
		if (!m_enemyPool[i]->IsDead())
		{
			m_enemyPool[i]->Process(deltatime);
		}
	}
}