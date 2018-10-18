#include "Enemy.h"
#include "Box2D/Box2D.h"
#include "sprite.h"
#include "backbuffer.h"
#include "FixtureType.h"
#include "logmanager.h"
#include <string>


bool Enemy::deleted = false;

Enemy::Enemy(int hp, FixtureType fixture, int enemySpawnX, int enemySpawnY)
	:Entity()
	, m_cultistMovementFrameOne(0)
	, m_cultistMovementFrameTwo(32)
	, m_currentFrame(0)
{
	m_monsterDeadPosition.Set(-40, -40);
	m_HP = hp;
	m_EnemyBox = new Box(.5f, .5f, fixture, enemySpawnX, enemySpawnY);
	m_fixtureType = fixture;
}


Enemy::~Enemy()
{
	delete m_pSprite;
	m_pSprite = 0;

	delete m_EnemyBox;
	m_EnemyBox = 0;
	
	if (!deleted)
	{
		delete m_pAnimatedSprite;
		m_pAnimatedSprite = 0;
		deleted = true;
	}
}

void Enemy::Process(float deltatime)
{
	Entity::Process(deltatime);
	m_pAnimatedSprite->Process(deltatime, 1);
	//m_EnemyBox->GetBody()->SetActive(false);
	if (m_currentFrame >= 1 )
	{
		m_monsterDead = false;
		m_currentFrame = 0;
		m_EnemyBox->GetBody()->SetActive(false);
		m_EnemyBox->GetBody()->SetTransform(m_monsterDeadPosition, 0);		
		SetDead(true);
	}
	if (m_monsterDead)
	{
		++m_currentFrame;
	}
}

void
Enemy::Initialise(b2World* world, AnimatedSprite* sprite)
{
	m_EnemyBox->SetOwner(this);
	m_EnemyBox->Initialisie(world);
	Entity::Initialise(sprite);
	m_pAnimatedSprite->AddFrame(m_cultistMovementFrameOne);
	m_pAnimatedSprite->AddFrame(m_cultistMovementFrameTwo);
	m_pAnimatedSprite->SetFrameSpeed(20.0f);
	m_pAnimatedSprite->SetFrameWidth(32);

	if (m_EnemyBox->IsDead())
	{
		m_EnemyBox->GetBody()->SetActive(false);
	}	
}

void
Enemy::Draw(BackBuffer* backBuffer)
{
	int PTM = Game::GetInstance().GetPTM();

	b2Vec2 pos = m_EnemyBox->GetBody()->GetPosition();

	b2PolygonShape* shape = ((b2PolygonShape*)m_EnemyBox->GetBody()->GetFixtureList()->GetNext()->GetShape());
	b2Vec2* v = shape->m_vertices;

	float width = v[1].x - v[0].x;
	float height = v[2].y - v[1].y;

	float x1 = (pos.x + v[0].x) * PTM;
	float y1 = (pos.y + v[0].y) * PTM;

	float x2 = width * PTM;
	float y2 = height * PTM;

	backBuffer->DrawAnimatedSprite(*m_pAnimatedSprite, static_cast<int>(x1), static_cast<int>(y1));	
	//m_EnemyBox->Draw(backBuffer);
}

void
Enemy::Damage(int damage)
{
	m_HP -= damage;
	SoundManager::GetInstance().MonsterHitSound();
	std::string test = std::to_string(m_HP);
	LogManager::GetInstance().Log(test.c_str());
	if (m_HP <= 0)
	{	
		m_currentFrame = 0;
		m_currentFrame = 0;
		RemoveMonster();
	}
}

void Enemy::RemoveMonster()
{		
	m_monsterDead = true;
	
}

FixtureType
Enemy::GetFixtureType()
{
	return m_fixtureType;
}


