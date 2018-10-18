#pragma once

#include "entity.h"
#include "FixtureType.h"
#include "Box2D/Box2D.h"
#include "backbuffer.h"


class Entity;

class AttackHitBox
	: public Entity
{
public:
	AttackHitBox();
	~AttackHitBox();
	void BeginContact(Entity* entity) override ;
	
	void Initailsise(b2World* world);
	b2Body* GetBody();

	bool isActive();
	void SetAttackActive(bool active);

	void Process(float delta);
	bool m_attackActive;

	void Draw(BackBuffer* backBuffer);

	b2Vec2 m_inavtivePosition;

protected:
	int m_currentAttackFrame;

private:
	float	m_width;
	float	m_height;
	b2Body* m_attackBody;
	int m_playerDamage;
	
	
};

