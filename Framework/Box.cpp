#include "Box.h"
#include "backbuffer.h"
#include "game.h"
#include<Box2D/Box2D.h>
#include "logmanager.h"
#include <string>
#include "myContactListener.h"
#include "FixtureType.h"




Box::Box(float width, float height, FixtureType fixture, int spawnX, int spawnY)
{
	m_width = width;
	m_height = height;	
	m_fixtureType = fixture;
	m_spawnX = spawnX;
	m_spawnY = spawnY;
}


Box::~Box()
{
}

bool
Box::Initialisie(b2World* world )
{
	//boby definition
	b2BodyDef m_PlayerBox;
	m_PlayerBox.type = b2_dynamicBody;
	m_PlayerBox.fixedRotation = true;
	
	
	//shape deffinition for main fixture
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(m_width, m_height);

	//fixture definition
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	//fixtureDef.friction = 1.0f;

	//create dynamic body
	m_PlayerBox.position.Set(static_cast<float32>(m_spawnX),static_cast<float32>( m_spawnY));
	m_body = world->CreateBody(&m_PlayerBox);
	//m_body->SetFixedRotation(true);
	
	//add main fixture
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(m_owner);

	//add foot sensor fixture
	dynamicBox.SetAsBox(2.0f/ m_PTM, 2.0f/ m_PTM , b2Vec2(0, 16.0f / m_PTM), 0);
	fixtureDef.isSensor = true;
	b2Fixture* footSensorFixture = m_body->CreateFixture(&fixtureDef);
	footSensorFixture->SetUserData((void*)m_fixtureType);

	

	return world;
}

void Box::SetOwner(Entity* owner)
{
	m_owner = owner;
	
}

void
Box::Draw(BackBuffer* backBuffer)
{
	
	int PTM = Game::GetInstance().GetPTM();

	b2Vec2 pos = m_body->GetPosition();

	
	b2PolygonShape* shape = ((b2PolygonShape*)m_body->GetFixtureList()->GetNext()->GetShape());
	b2Vec2* v = shape->m_vertices;

	float width = v[1].x - v[0].x;
	float height = v[2].y - v[1].y;

	float x1 = (pos.x + v[0].x) * PTM;
	float y1 = (pos.y + v[0].y) * PTM;

	float x2 = width * PTM;
	float y2 = height * PTM;

	if (m_fixtureType == FixtureType::ENEMY)
	{
		backBuffer->SetDrawColour(0, 255, 0);
	}
	else
	{
		backBuffer->SetDrawColour(0,0,255);
	}
	
	
	backBuffer->DrawRectangle(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2));
//	backBuffer->DrawRectangle(static_cast<int>(pos.x*PTM), static_cast<int>(pos.y*PTM),static_cast<int>( width*PTM),static_cast<int>( height*PTM));
}
void
Box::Process(float deltatime)
{
	Entity::Process(deltatime);
}

b2Body*
Box::GetBody()
{
	return m_body;
}


