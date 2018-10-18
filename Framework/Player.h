#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "entity.h"
#include "Box2D/Box2D.h"
#include "FixtureType.h"
#include "Box.h"
#include "sprite.h"
#include "backbuffer.h"
#include "game.h"
#include "AttackHitBox.h"
#include "SoundManager.h"
#include "animatedsprite.h"
#include "inputhandler.h"



class Player : public Entity

{
public:
	Player(FixtureType fixture);
	~Player();
	
	void Process(float deltatime);
	void Initialise(b2World* world, AnimatedSprite* sprite);
	void Draw(BackBuffer* backBuffer);
	Box* GetPlayerBox();
	void Attack();

	void movePlayerBox();
	
	int GetMovementState();

	void PlayerJump(bool m_forceOn);
	void MovePlayerBoxRight();
	void MovePlayerBoxLeft();
	void StopMovement();

	int m_spriteSheetRunning;
	int m_spriteSheetJumping;
	int m_spriteSheetStandingStill;
	int m_spriteSheetAttack;
	
	int m_movementState;
	enum moveState
	{
		MOVE_LEFT,
		MOVE_RIGHT,
		JUMP,
		ATTACK,
		MOVE_STOP
	};

private:
	int m_PlayerHp;
	int m_PlayerSheald;

	int m_playerSpawnX;
	int m_playerSpawnY;

	Box* m_PlayerBox;
	AttackHitBox* m_attackBox;
	float m_offset;
	bool moveningRight = false;
	bool flip = false;

	
	

};

#endif // !__PLAYER_H__


