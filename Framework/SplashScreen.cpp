#include "SplashScreen.h"



SplashScreen::SplashScreen()
	:Entity()
{
}


SplashScreen::~SplashScreen()
{
}

void
SplashScreen::Draw(BackBuffer * backBuffer)
{
	Entity::Draw(*backBuffer);
}
void
SplashScreen::Process(float deltatime)
{
	Entity::Process(deltatime);
}