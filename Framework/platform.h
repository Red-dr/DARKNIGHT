#pragma once

#include<Box2D/Box2D.h>
#include "entity.h"
#include "FixtureType.h"
class Platform : public Entity
{
public:
	Platform(float x, float y, float width, float hight);
	~Platform();
	bool Initialisie(b2World* world);
	void Draw(BackBuffer* backBuffer);
	void Process(float deltatime);

	b2Body* m_platform;
private:

	b2Body* GetPlatForm();

	float m_platformX;
	float m_platformY;
	float m_width;
	float m_hight;

};

