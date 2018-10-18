// COMP710 GP 2D Framework 2018

// This includes:
#include "game.h"
#include "Player.h"
#include "Enemy.h"


// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"

#include "fmod.hpp"
#include "fmod_errors.h"
#include "animatedsprite.h"
#include "Box.h"
#include "Box2D/Box2D.h"
#include "platform.h"
#include "FixtureType.h"
#include "Objectpools.h"
#include "SoundManager.h"


// Library includes:
#include <cassert>
#include <SDL.h>
#include <cstdio>
#include <vector>
#include <string>
//#include <fmod_errors.h>


// Static Members:
Game* Game::sm_pInstance = 0;

Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{ 
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

void 
Game::DestroyInstance()
{
	delete sm_pInstance; 
	sm_pInstance = 0;
}

Game::Game()
	: m_pBackBuffer(0)
	, m_pInputHandler(0)
	, m_looping(true)
	, m_executionTime(0)
	, m_elapsedSeconds(0)
	, m_frameCount(0)
	, m_FPS(0)
	, m_numUpdates(0)
	, m_lastTime(0)
	, m_lag(0)
	, m_playerXPos(400)
	, m_playerYPos(500)
	, m_player(0)
	, m_enemyXpos(0)
	, m_enemyYpos(0)
	, m_ptm(30)
	, m_forceOn(true)
	, CLUTIST_HP(0)
	
	
{
	
}

Game::~Game()
{
	

	delete m_pInputHandler;
	m_pInputHandler = 0;

	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete world;
	world = 0;

	delete m_rightWall;
	m_rightWall = 0;

	delete m_roof;
	m_roof = 0;
	
	delete m_leftWall;
	m_leftWall = 0;

	delete m_middlePlatform;
	m_middlePlatform = 0;

	delete m_leftPlatform;
	m_leftPlatform = 0;

	delete m_rightPlatform;
	m_rightPlatform = 0;

	delete m_splashScreen;
	m_splashScreen = 0;

	delete m_objectPool;
	m_objectPool = 0;

	delete m_player;
	m_player = 0;

	SoundManager::GetInstance().DestroyInstance();
	
		
}

bool 
Game::Initialise()
{
	


	//inializing the world with box2D
	//gravity
	b2Vec2 gravity(0.0f, 10.0f);
	world = new b2World(gravity);
	//contact listeners 
	world->SetContactListener(&m_myContactListenerInstance);

	//ground 
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 30.0f);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &groundBox;
	myFixtureDef.friction = 1;
	//
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	//roof
	m_roof = new Platform(0.0f /GetPTM(), 1.0f, 1500.0f / GetPTM(), 20.0f/ GetPTM());
	m_roof->Initialisie(world);

	//left wall
	m_leftWall = new Platform(10.0f / GetPTM() , 0.f, 10.f / GetPTM(), 1500.0f / GetPTM());
	m_leftWall->Initialisie(world);

	//right wall
	m_rightWall = new Platform(790.0f/GetPTM(), 0.0f, 10.f / GetPTM(), 1500.0f / GetPTM());
	m_rightWall->Initialisie(world);


	//middle jumpping platform 
	m_middlePlatform = new Platform(400.0f / GetPTM(), 500.0f / GetPTM(), 150.f / GetPTM(), 10.f / GetPTM());
	m_middlePlatform->Initialisie(world);

	//left jumpping platform 
	m_leftPlatform = new Platform(100.0f / GetPTM(), 400.0f / GetPTM(), 150.f / GetPTM(), 10.f / GetPTM());
	m_leftPlatform->Initialisie(world);

	//right jumpping platform
	m_rightPlatform = new Platform(700.0f / GetPTM(), 400.0f / GetPTM(), 150.f / GetPTM(), 10.f / GetPTM());
	m_rightPlatform->Initialisie(world);

	//time and iterations 
	m_timeStep = 1.0f / 60.0f;
	m_velocityIterations = 6;
	m_positionIterations = 2;


	const int width = 800;
	const int height = 600;

	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(width, height))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}


	// making the player body and ataching the sprite
	
	AnimatedSprite* pPlayerSprite = m_pBackBuffer->CreateAnimatedSprite("assets\\player\\player_sprite_sheet.png");
	m_player = new Player(FixtureType::PLAYER);
	m_player->Initialise(world, pPlayerSprite);
	
	//makeing the enemy
	AnimatedSprite* pCultistSprite = m_pBackBuffer->CreateAnimatedSprite("assets\\monster\\cultist_sheet.png");
	m_objectPool = new Objectpools();
	m_objectPool->Initialise(world, pCultistSprite);

	////making the splash screen 
	Sprite* pSplashscreen = m_pBackBuffer->CreateSprite("assets\\AUT_LOGO.png");
	m_splashScreen = new SplashScreen();
	m_splashScreen->Initialise(pSplashscreen);
	

	//makeing the sounds
	SoundManager::GetInstance().Init();


	//delta time 
	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;

	
	return (true);
}

bool 
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);
	m_pInputHandler->ProcessInput(*this);
	
	if (m_looping)
	{
		int current = SDL_GetTicks();
		float deltaTime = (current - m_lastTime) / 1000.0f;
		m_lastTime = current;

		m_executionTime += deltaTime;

		m_lag += deltaTime;

		while (m_lag >= stepSize)
		{
			Process(stepSize);

			m_lag -= stepSize;

			++m_numUpdates;
		}
		
		Draw(*m_pBackBuffer);
	}
	
//	SDL_Delay(1);

	return (m_looping);
}

void 
Game::Process(float deltaTime)
{
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;
	if (m_splashOn) 
	{
		if (m_elapsedSeconds > 5)
		{
			m_splashOn = false;
		}
	}
	else
	{
		// Frame Counter:
		if (m_elapsedSeconds > 1)
		{
			m_elapsedSeconds -= 1;
			m_FPS = m_frameCount;
			m_frameCount = 0;
		}
		world->Step(m_timeStep, m_velocityIterations, m_positionIterations);
		m_player->Process(deltaTime);
		m_objectPool->Process(deltaTime);

		SoundManager::GetInstance().SoundUpdate();
	}

	
}

void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;
		backBuffer.Clear();
	if (m_splashOn)
	{
		m_splashScreen->Draw(&backBuffer);
		
	}
	else
	{

		
		backBuffer.SetClearColour(50, 32, 32);
		//drawing the world
		m_roof->Draw(&backBuffer);
		m_leftWall->Draw(&backBuffer);
		m_rightWall->Draw(&backBuffer);


		// draw platforms
		m_middlePlatform->Draw(&backBuffer);
		m_leftPlatform->Draw(&backBuffer);
		m_rightPlatform->Draw(&backBuffer);

		//drawing the entitys

		m_player->Draw(&backBuffer);
		m_objectPool->Draw(&backBuffer);

	}

	
	backBuffer.Present();
}

void 
Game::Quit()
{
	m_looping = false;
}

void
Game::StopMovement()
{
	
	m_player->StopMovement();
}

void
Game::JumpPlayerBox(bool m_forceOn)
{
	SoundManager::GetInstance().PlayerJumpSound();
	m_player->PlayerJump(m_forceOn);
}

void
Game::PlayerAttack()
{
	m_player->Attack();
}

void Game::MovePlayerBoxRight()
{
		m_player->MovePlayerBoxRight();	
}

void Game::MovePlayerBoxLeft()
{
		m_player->MovePlayerBoxLeft();	
}

void 
Game::SpawnEnemy(int x, int y)
{
	//TODO
	
}
int
Game::GetPTM()
{
	return static_cast<int>(m_ptm);
}



