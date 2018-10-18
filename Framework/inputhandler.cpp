// COMP710 GP 2D Framework 2018

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"
#include "logmanager.h"
#include "myContactListener.h"

// Library includes:
#include <cassert>
#include <iostream>
#include <string>



InputHandler::InputHandler()
	: m_pGameController(0)
{

}

InputHandler::~InputHandler()
{
	if (m_pGameController)
	{
		SDL_JoystickClose(m_pGameController);
		m_pGameController = 0;
	}
}

bool
InputHandler::Initialise()
{
	int numControllesr = SDL_NumJoysticks();
	SDL_JoystickEventState(SDL_ENABLE);
	m_pGameController = SDL_JoystickOpen(0);

	if (!m_pGameController)
	{
		LogManager::GetInstance().Log("No controller detected!");
	}

	return (true);
}

void
InputHandler::ProcessInput(Game& game)
{
	// W02.1: Receive Input Events below...
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (e.type == SDL_JOYBUTTONDOWN)
		{

			LogManager::GetInstance().Log("butten pressed");

			if (e.jbutton.button == 0)
			{
				if (myContactListener::CanJumpNow())
				{
					LogManager::GetInstance().Log("jump");
					game.JumpPlayerBox(true);
				}
			}
			else if (e.jbutton.button == 1)
			{
				game.PlayerAttack();
			}

		}
		else if (e.type == SDL_JOYAXISMOTION)
		{
			//only checking the X axis on the left alalong stick 1= Y axix
			if (e.jaxis.axis == 0)
			{
				//checing the dead zone to the left 
				if (e.jaxis.value < -20000)
				{
					game.MovePlayerBoxLeft();
				}
				//checking dead zone to the right
				else if (e.jaxis.value > 20000)
				{
					game.MovePlayerBoxRight();
				}
				else
				{
				//	game.StopMovement();
				}
			}
		}
		if (e.key.keysym.sym == SDLK_ESCAPE)
		{
			game.Quit();
		}
		else if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_d)
			{
				game.MovePlayerBoxRight();


			}
			if (e.key.keysym.sym == SDLK_a)
			{
				game.MovePlayerBoxLeft();


			}
			if (e.key.keysym.sym == SDLK_SPACE && e.key.repeat == 0)
			{
				if (myContactListener::CanJumpNow())
				{

					game.JumpPlayerBox(true);
				}
			}
			if (e.key.keysym.sym == SDLK_LSHIFT && e.key.repeat == 0)
			{
				game.PlayerAttack();
			}
		}
		else if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym == SDLK_d)
			{
				game.StopMovement();

			}
			if (e.key.keysym.sym == SDLK_a)
			{
				game.StopMovement();

			}
		}
	}
}



