// COMP710 GP 2D Framework 2018

// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "backbuffer.h"
#include "logmanager.h"
#include "animatedsprite.h"
#include "box.h"

// Library includes:
#include <cassert>
#include <string>

Entity::Entity()
	: m_pSprite(0)
	, m_x(0.0f)
	, m_y(0.0f)
	, m_velocityX(0.0f)
	, m_velocityY(0.0f)
	, m_dead(false)
	, m_pAnimatedSprite(0)
	, m_PTM(30)
	
{

}

Entity::~Entity()
{
	delete m_pSprite;
	m_pSprite = 0;

	
}

void 
Entity::BeginContact(Entity* entity)
{
	
	//do nothing
}

bool
Entity::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	return (true);
}
bool
Entity::Initialise(AnimatedSprite* sprite)
{
	assert(sprite);
	m_pAnimatedSprite = sprite;
	

	return (true);
}

void 
Entity::Process(float deltaTime)
{
	// W02.1: Generic position update, based upon velocity (and time).

	//;
	//std::string to_string(int m_velocityX);
//	LogManager::GetInstance().Log(test.c_str());
	m_x = m_x + m_velocityX * deltaTime;
	m_y = m_y + m_velocityY * deltaTime;

	// W02.1: Boundary checking and position capping. 
	if (m_x <= 0) {
		m_x = 1;
	}
	else if (m_x >= 770)
	{
		m_x = 770;
	}


	//m_PlayerBox->Process(deltaTime);

}

void 
Entity::Draw(BackBuffer& backBuffer )
{
	assert(m_pSprite);
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
	m_pSprite->Draw(backBuffer);
}



bool
Entity::IsCollidingWith(Entity& e)
{
	// W02.3: Generic Entity Collision routine.
	float x1 = GetSpritePositionX();
	float y1 = GetSpritePositionY();
	float x2 = e.GetSpritePositionX();
	float y2 = e.GetSpritePositionY();
	float r1 = m_pSprite->GetWidth() / 2.0f;
	float r2 = e.m_pSprite->GetWidth() / 2.0f;
	bool colition = false;

	// W02.3: Does this object collide with the e object?
	float collide = sqrt((powf((x2 - x1),2) + powf((y2 - y1) , 2))) - r1 - r2;

	// W02.3: Create a circle for each entity (this and e).

	// W02.3: Check for intersection.
	if (collide <= 0)
	{
		colition = true;
	//	LogManager::GetInstance().Log(" HIT");
	}
	// W02.3: Using circle-vs-circle collision detection.

	// W02.3: Return result of collision.
	
	return (colition); // W02.3 Change return value!
}

void 
Entity::SetDead(bool dead)
{
	m_dead = dead;
}

void
Entity::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

void
Entity::SetPositionX(float x)
{
	m_x = x;
}

void
Entity::SetPositionY(float y)
{
	m_y = y;
}

float 
Entity::GetPositionX() const
{
	return (m_x);
}

float 
Entity::GetPositionY() const
{
	return (m_y);
}

float 
Entity::GetHorizontalVelocity() const
{
	return (m_velocityX);
}

float 
Entity::GetVerticalVelocity() const
{
	return (m_velocityY);
}

void 
Entity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void 
Entity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}

float
Entity::GetSpritePositionX()
{
	float x;

	x = m_x + (m_pSprite->GetWidth() / 2);
	return x;
}

FixtureType 
Entity::GetFixtureType()
{
	return m_fixtureType;
}

float
Entity::GetSpritePositionY()
{
	float y;
	y = m_y + (m_pSprite->GetHeight() / 2);
	return y;
}

bool
Entity::IsDead() const
{
	return m_dead;

}