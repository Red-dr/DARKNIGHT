// COMP710 GP 2D Framework 2018
#ifndef __INPUTHANDER_H__
#define __INPUTHANDER_H__

// Library includes:
#include <SDL.h>
#include "player.h"

// Forward Declarations:
class Game;
class myContactListener;

class InputHandler
{
	//Member Methods:
public:
	InputHandler();
	~InputHandler();

	bool Initialise();
	void ProcessInput(Game& game);



	

	enum movement {
		MOVE_LEFT,
		MOVE_STOP,
		MOVE_RIGHT,
		MOVE_JUMP,
		PLAYER_ATTACK

	};


protected:

private:
	InputHandler(const InputHandler& inputHandler);
	InputHandler& operator=(const InputHandler& inputHandler);

	//Member Data:
public:

protected:
	SDL_Joystick* m_pGameController;

	

private:

};

#endif // __INPUTHANDER_H__
