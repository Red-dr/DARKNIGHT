#include "Player.h"
#include "entity.h"
#include "FixtureType.h"
#include "Box.h"
#include "backbuffer.h"
#include <iostream>
#include "game.h"
#include "sprite.h"
#include "Box2D/Box2D.h"
#include "AttackHitBox.h"




Player::Player(FixtureType fixture)
	:Entity()
	, m_PlayerHp(100)
	, m_PlayerSheald(100)
	, m_offset(1.0f)
	, m_spriteSheetJumping(128)
	, m_spriteSheetStandingStill(0)
	, m_spriteSheetRunning(32)
	, m_spriteSheetAttack(60)
	, m_playerSpawnX(10)
	, m_playerSpawnY(4)
{
	m_PlayerBox = new Box(.5f, .5f, fixture, m_playerSpawnX, m_playerSpawnY);
	m_attackBox = new AttackHitBox();
	
}


Player::~Player()
{
	delete m_pSprite;
	m_pSprite = 0;

	delete m_PlayerBox;
	m_PlayerBox = 0;

	delete m_attackBox;
	m_attackBox = 0;

	delete m_pAnimatedSprite;
	m_pAnimatedSprite = 0;
}

void
Player::Process(float deltatime)	
{
	Entity::Process(deltatime);
	m_attackBox->Process(deltatime);
	m_pAnimatedSprite->Process(deltatime, m_movementState);
}

void
Player::Initialise(b2World* world, AnimatedSprite* sprite)
{
	m_PlayerBox->SetOwner(this);
	m_PlayerBox->Initialisie(world);
	m_attackBox->Initailsise(world);
	Entity::Initialise(sprite);
	m_pAnimatedSprite->AddFrame(m_spriteSheetStandingStill);
	m_pAnimatedSprite->AddFrame(m_spriteSheetRunning);
	m_pAnimatedSprite->AddFrame(m_spriteSheetRunning + 32);
	m_pAnimatedSprite->AddFrame(m_spriteSheetJumping);
	m_pAnimatedSprite->AddFrame(m_spriteSheetAttack);
	m_pAnimatedSprite->SetFrameSpeed(20.0f);
	m_pAnimatedSprite->SetFrameWidth(32);
}

void 
Player::Draw(BackBuffer* backBuffer)
{

	int PTM = Game::GetInstance().GetPTM();

	b2Vec2 pos = m_PlayerBox->GetBody()->GetPosition();

	b2PolygonShape* shape = ((b2PolygonShape*)m_PlayerBox->GetBody()->GetFixtureList()->GetNext()->GetShape());
	b2Vec2* v = shape->m_vertices;

	float width = v[1].x - v[0].x;
	float height = v[2].y - v[1].y;

	float x1 = (pos.x + v[0].x) * PTM;
	float y1 = (pos.y + v[0].y) * PTM;

	float x2 = width * PTM;
	float y2 = height * PTM;

	/*if (flip)
	{
		backBuffer->DrawAnimatedSpriteFliped(*m_pAnimatedSprite, static_cast<int>(x1), static_cast<int>(y1));
	}
	else
	{
		
	}*/
	backBuffer->DrawAnimatedSprite(*m_pAnimatedSprite, static_cast<int>(x1), static_cast<int>(y1));
	
	//m_attackBox->Draw(backBuffer);
}

void
Player::Attack()
{
	if (!m_attackBox->m_attackActive)
	{
		m_movementState = moveState::ATTACK;
		m_attackBox->SetAttackActive(true);

		b2Vec2 pos = m_PlayerBox->GetBody()->GetPosition();
		if (moveningRight)
		{
			pos.x += m_offset;
		}
		else if (!moveningRight)
		{
			pos.x -= m_offset;
		}
		m_attackBox->GetBody()->SetTransform(pos, 0);	
		SoundManager::GetInstance().PlayerAttackSound();
	}
}

void Player::movePlayerBox()
{
	b2Vec2 vel = m_PlayerBox->GetBody()->GetLinearVelocity();
	float desiredVel = 0;
	switch (m_movementState)
	{	 
	case moveState::MOVE_LEFT:  desiredVel = -5; break;
	case moveState::MOVE_STOP:  desiredVel = 0; break;
	case moveState::MOVE_RIGHT: desiredVel = 5; break;
	}	 
	float velChange = desiredVel - vel.x;
	float force = m_PlayerBox->GetBody()->GetMass() * velChange;// / (1 / 60.0); //f = mv/t
	m_PlayerBox->GetBody()->ApplyLinearImpulse(b2Vec2(force, 0), m_PlayerBox->GetBody()->GetWorldCenter(), true);
}

Box*
Player::GetPlayerBox()
{
	return m_PlayerBox;
}

int
Player::GetMovementState()
{
	return m_movementState;
}

void Player::PlayerJump(bool m_forceOn)
{
	m_PlayerBox->GetBody()->SetFixedRotation(true);
	float impulse =m_PlayerBox->GetBody()->GetMass() * -0.35f;
	m_PlayerBox->GetBody()->ApplyLinearImpulse(b2Vec2(0, impulse * static_cast<float32>(30)),m_PlayerBox->GetBody()->GetWorldCenter(), m_forceOn);
	m_movementState = moveState::JUMP;

}

void Player::MovePlayerBoxRight()
{
	m_movementState = moveState::MOVE_RIGHT;
	moveningRight = true;
	flip = true;
	movePlayerBox();
}

void Player::MovePlayerBoxLeft()
{
	m_movementState = moveState::MOVE_LEFT;
	moveningRight = false;
	flip = false;
	movePlayerBox();
	
}

void Player::StopMovement()
{
	m_movementState = moveState::MOVE_STOP;
	flip = false;
	movePlayerBox();
}


