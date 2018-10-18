#ifndef __SPLASHSCREEN_H__
#define __SPLASHSCREEN_H__

#include "backbuffer.h"
#include "entity.h"
class SplashScreen : public Entity
{


public:

	SplashScreen();
	~SplashScreen();


	void Draw(BackBuffer* backBuffer);
	void Process(float deltatime);

};

#endif // !__SPLASHSCREEN_H__

