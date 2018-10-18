#include "AttackHitBox.h"
#include "FixtureType.h"
#include "Box2d/Box2D.h"
#include "Enemy.h"
#include "game.h"
#include "logmanager.h"


//static members


AttackHitBox::AttackHitBox() :
	m_width(20)
	, m_height(20)
	, m_currentAttackFrame(0)
	, m_playerDamage(5)

{
	m_inavtivePosition.Set(-50, -50);
}


AttackHitBox::~AttackHitBox()
{
}

void
AttackHitBox::BeginContact(Entity* entity)
{
	//checking to see if the entity is a enemey if so attacking it and doing damage to it
	if (entity->GetFixtureType() == FixtureType::ENEMY)
	{
		if (m_attackActive)
		{
			(static_cast<Enemy*>(entity))->Damage(m_playerDamage);
			
			m_currentAttackFrame = 0;
		}
	}
}

void 
AttackHitBox::Initailsise(b2World* world)
{

	b2BodyDef m_AttackBox;
	m_AttackBox.type = b2_kinematicBody;
	m_AttackBox.fixedRotation = true;

	b2PolygonShape kinematicBox;
	kinematicBox.SetAsBox(m_width/30, m_height/30);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &kinematicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.isSensor = true;

	m_attackBody = world->CreateBody(&m_AttackBox);
	
	m_attackBody->CreateFixture(&fixtureDef);
	m_attackBody->SetUserData(this);
	//teststring = "attack hitbox";
}

b2Body*
AttackHitBox::GetBody()
{
	return m_attackBody;
}

bool 
AttackHitBox::isActive()
{
	return m_attackActive;
}

void
AttackHitBox::SetAttackActive(bool active)
{
	m_attackActive = active;
	m_currentAttackFrame = 0;
}

void 
AttackHitBox::Process(float delta)
{
	if (m_currentAttackFrame >= 1)
	{
		m_attackActive = false;
		m_currentAttackFrame = 0 ;
		m_attackBody->SetTransform(m_inavtivePosition, 0);
	}

	if (m_attackActive)
	{
		++m_currentAttackFrame;	
	}
	
}

void
AttackHitBox::Draw(BackBuffer* backBuffer)
{

	int PTM = Game::GetInstance().GetPTM();

	b2Vec2 pos = m_attackBody->GetPosition();

	b2PolygonShape* shape = ((b2PolygonShape*)m_attackBody->GetFixtureList()->GetShape());
	b2Vec2* v = shape->m_vertices;

	float width = v[1].x - v[0].x;
	float height = v[2].y - v[1].y;

	float x1 = (pos.x + v[0].x) * PTM;
	float y1 = (pos.y + v[0].y) * PTM;

	float x2 = width * PTM;
	float y2 = height * PTM;

	backBuffer->SetDrawColour(0, 0, 255);
	backBuffer->DrawRectangle(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2));
}
