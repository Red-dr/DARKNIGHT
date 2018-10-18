#pragma once

//includes
#include<Box2D/Box2D.h>
#include "entity.h"
#include "FixtureType.h"
#include "AttackHitBox.h"



class Box : public Entity
{


public:
	Box(float witdh, float height, FixtureType fixture,int spawnX, int spawnY);
	~Box();

	bool Initialisie(b2World* world );
	void SetOwner(Entity* owner);
	void Draw(BackBuffer* backBuffer);

	void Process(float deltatime);

	b2Body* GetBody();

	


private:
	float m_width;
	float m_height;
	int m_spawnX;
	int m_spawnY;
	Entity* m_owner;

	

	b2Body* m_body;

};

