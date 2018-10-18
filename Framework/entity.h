// COMP710 GP 2D Framework 2018
#ifndef __ENTITY_H__
#define __ENTITY_H__


#include"FixtureType.h"
#include <string>
// Forward Declarations:
class BackBuffer;
class Sprite;
class AnimatedSprite;
class box;


class Entity
{
	//Member Methods:
public:
	Entity();
	~Entity();
	virtual void BeginContact(Entity* entity);
	bool Initialise(Sprite* sprite);

	bool Initialise(AnimatedSprite * sprite);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void SetDead(bool dead);
	bool IsDead() const;

	bool IsCollidingWith(Entity& e);

	void SetPosition(float x, float y);
	void SetPositionX(float x);
	void SetPositionY(float y);

	float GetPositionX() const;
	float GetPositionY() const;

	float GetHorizontalVelocity() const;
	void SetHorizontalVelocity(float x); 

	float GetVerticalVelocity() const;
	void SetVerticalVelocity(float y);

	float GetSpritePositionY();
	float GetSpritePositionX();




	FixtureType GetFixtureType();
	char* teststring = "Entity";

protected:

private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);

	//Member Data:
public:
	int m_frameCount;

protected:
	Sprite* m_pSprite;
	AnimatedSprite* m_pAnimatedSprite;

	FixtureType m_fixtureType;


	float m_x;
	float m_y;

	float m_velocityX;
	float m_velocityY;

	int m_PTM;
	
	bool m_dead;

private:

};

#endif //__ENTITY_H__
