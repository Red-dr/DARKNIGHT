#include "platform.h"
#include "backbuffer.h"
#include "game.h"
#include<Box2D/Box2D.h>
#include "logmanager.h"
#include <string>
#include "FixtureType.h"


Platform::Platform(float x, float y, float width, float hight) 
{
	m_platformX = x;
	m_platformY = y;
	m_width = width;
	m_hight = hight;
	
}


Platform::~Platform()
{

}

bool
Platform::Initialisie(b2World* world)
{
	b2BodyDef roofBodyDef;
	roofBodyDef.position.Set(m_platformX, m_platformY);
	 m_platform = world->CreateBody(&roofBodyDef);

	b2PolygonShape topBox;
	topBox.SetAsBox(m_width, m_hight);
	m_platform->CreateFixture(&topBox, 0.0f);
	m_platform->SetUserData(this);

	return world;
}

void
Platform::Draw(BackBuffer* backBuffer)
{
	int PTM = Game::GetInstance().GetPTM();

	b2Vec2 pos = m_platform->GetPosition();
	b2PolygonShape* shape = ((b2PolygonShape*)m_platform->GetFixtureList()->GetShape());
	b2Vec2* v = shape->m_vertices;

	float width = v[1].x - v[0].x;
	float height = v[2].y - v[1].y;

	float x1 = (pos.x + v[0].x) * PTM;
	float y1 = (pos.y + v[0].y) * PTM;

	float x2 = width * PTM;
	float y2 = height * PTM;

	/*std::string test = std::to_string(pos.x*PTM);
	std::string test2 = std::to_string(m_platform->GetPosition().y);
	
	LogManager::GetInstance().Log(test.c_str());
	LogManager::GetInstance().Log(test2.c_str());*/
	backBuffer->SetDrawColour(0,0, 0);
	backBuffer->DrawRectangle(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2));

}
void
Platform::Process(float deltatime)
{
	Entity::Process(deltatime);
}

b2Body* 
Platform::GetPlatForm()
{
	return m_platform;
}

