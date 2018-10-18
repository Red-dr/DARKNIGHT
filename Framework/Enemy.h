#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "entity.h"
#include "Box.h"

#include "backbuffer.h"
#include "FixtureType.h"
#include "game.h"
#include "fmod.hpp"
#include "SoundManager.h"


class BackBuffer;
class box; 

class Enemy : public Entity
{
public:
	Enemy(int hp, FixtureType fixture , int enemySpawnX, int enemySpawnY);
	~Enemy();

	void Process(float deltatime);
	int m_HP;
	void Initialise(b2World* world ,AnimatedSprite* sprite);
	void Draw(BackBuffer* backBuffer);
	void Damage(int damage);
	void RemoveMonster();
	FixtureType GetFixtureType();
	
	bool m_monsterDead = false;

protected:
	
private:
	Box* m_EnemyBox;
	int m_cultistMovementFrameOne;
	int m_cultistMovementFrameTwo;
	b2Vec2 m_monsterDeadPosition;
	
	int m_currentFrame;
	static bool deleted;
};

#endif // __ENEMY_H__

