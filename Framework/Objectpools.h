#pragma once
#include "Enemy.h"
#include "FixtureType.h"
#include "backbuffer.h"
#include "Box2D/Box2D.h"
#include "entity.h"
#include "animatedsprite.h"
#include <cstdlib>

class Objectpools
{
public:
	Objectpools();
	~Objectpools();

	void Process(float deltatime);
	Enemy GetEnemey();
	void Draw(BackBuffer* backBuffer);
	bool Initialise(b2World* world, AnimatedSprite* sprite);
	
private:
	int MAX_ENEMY_SIZE;
	const int CULTIST_HP;
	Enemy** m_enemyPool;
	int m_enemySpawnX;
	int m_enemySpawnY;

	bool m_active;

};

