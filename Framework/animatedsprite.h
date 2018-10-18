#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

#include "sprite.h"
#include "backbuffer.h"
#include <vector>
#include "inputhandler.h"
#include "Player.h"
#include "game.h"



class AnimatedSprite : public Sprite
{
	// Methods:
public:
	AnimatedSprite();
	~AnimatedSprite();

	bool Initialise(Texture& texture);
	void AddFrame(int x);

	void Process(float deltaTime, int movestate);
	void Draw(BackBuffer& backbuffer);

	void SetFrameSpeed(float f);
	void SetFrameWidth(int w);

	int GetFrameWidth();
	int GetCurrentFrame();

	void Pause();
	bool IsPaused();

	bool IsAnimating();
	void StartAnimating();

	bool IsLooping();
	void SetLooping(bool b);

	int GetX() const;
	int GetY() const;
	
	

protected:
	
private:
	

	// Fields:
public:

protected:
	// W03.4: Add a field, the container for frame coordinates.
	std::vector<int> m_frameCoords;
	Texture * m_pTexture;
	float m_frameSpeed;
	int m_frameWidth;

	float m_timeElapsed;
	int m_currentFrame;

	bool m_paused;
	bool m_loop;
	bool m_animating;

private:

};

#endif // __ANIMATEDSPRITE_H__
