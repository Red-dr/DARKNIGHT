// COMP710 GP 2D Framework 2018
#ifndef __GAME_H__
#define __GAME_H__
// standed libaray
#include <vector>
//local incudes
#include "fmod.hpp"
#include "Box2D/Box2D.h"
#include "inputhandler.h"
#include "myContactListener.h"
#include "SoundManager.h"
#include "SplashScreen.h"

#include <chrono>






// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class Player;
class Enemy;
class Bullet;
class Explosion;
class Box;
class Platform;
//class myContactListener;
class Objectpools;

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();

	bool Initialise();
	bool DoGameLoop();
	void Quit();

	void JumpPlayerBox(bool m_forceOn);
	void StopMovement();
	void PlayerAttack();
	void MovePlayerBoxRight();
	void MovePlayerBoxLeft();
	int GetPTM();

	void SpawnEnemy(int x, int y);

protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	//Member Data:
public:
	myContactListener m_myContactListenerInstance;
	

protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	bool m_looping;

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	int m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	float m_playerXPos;
	float m_playerYPos;
	float m_enemyXpos;
	float m_enemyYpos;
	float m_ptm;
	const int CLUTIST_HP;

	float32 m_timeStep;
	int32 m_velocityIterations;
	int32 m_positionIterations;

	bool m_drawDebugInfo;
	bool m_forceOn;

	bool m_splashOn = true;
	
	b2World* world;
	// Game Entities:
	
	Player* m_player;

	//Box* m_PlayerBox;
	Enemy* m_enemytest;
	Objectpools* m_objectPool;

	Platform* m_roof;
	Platform* m_leftWall;
	Platform* m_rightWall;
	Platform* m_middlePlatform;
	Platform* m_leftPlatform;
	Platform* m_rightPlatform;

	//splashscreen
	SplashScreen* m_splashScreen;

	

private:

};

#endif // __GAME_H__
