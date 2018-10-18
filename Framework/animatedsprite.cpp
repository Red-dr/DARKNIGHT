// This includes:
#include "animatedsprite.h"

// Local includes:
#include "texture.h"
#include "backbuffer.h"
#include "player.h"
#include "logmanager.h"
#include "Enemy.h"

AnimatedSprite::AnimatedSprite()
: m_frameSpeed(0.0f)
, m_frameWidth(0)
, m_timeElapsed(0.0f)
, m_currentFrame(0)
, m_paused(false)
, m_loop(false)
, m_animating(false)
{

}

AnimatedSprite::~AnimatedSprite()
{
	//delete m_pAnimatedSprite;
}

bool
AnimatedSprite::Initialise(Texture& texture)
{
	m_frameWidth = 0;
	m_frameSpeed = 0;

	m_loop = false;
	m_paused = false;
	m_animating = true;

	Sprite::Initialise(texture);

	StartAnimating();

	return (true);
}

void 
AnimatedSprite::AddFrame(int x)
{
	// W03.4: Add the x coordinate to the frame coordinate container.
	m_frameCoords.push_back(x);

}

void 
AnimatedSprite::Process(float deltaTime, int movestate)
{
	// W03.4: If not paused...
	// W03.4: Count the time elapsed.
	m_timeElapsed += deltaTime;
	if (m_loop)
	{
		return;
	}

	if (m_paused)
	{
		m_currentFrame = m_currentFrame;
	}

	// W03.4: If the time elapsed is greater than the frame speed.
	
	if (m_animating)
	{		
		if (movestate == Player::moveState::MOVE_LEFT)
		{
			++m_timeElapsed;
			m_currentFrame = 1;			
			if (m_timeElapsed >= m_frameSpeed)
			{		
				m_currentFrame = 2;
				m_timeElapsed = 0.0f;		
			}		
		}
		else if (movestate == Player::moveState::JUMP)
		{
			m_currentFrame = 3;
			++m_timeElapsed;
			if (m_timeElapsed >= m_frameSpeed)
			{
				m_currentFrame = 0;
				m_timeElapsed = 0.0f;
			}		
		}
		else if (movestate == Player::moveState::ATTACK)
		{
			m_currentFrame = 4;
			++m_timeElapsed;
			if (m_timeElapsed >= m_frameSpeed)
			{
				m_currentFrame = 0;
				m_timeElapsed = 0.0f;
			}
		}
		else
		{
			m_currentFrame = 0;
		}


	}

}

void 
AnimatedSprite::Draw(BackBuffer& backbuffer)
{
	// W03.4: Draw the particular frame into the backbuffer.
	if (m_animating)
	{
		backbuffer.DrawAnimatedSprite(*this);
	}
	//          What is the current frame's x coordinate?
	//          What is the frame width?
}

void 
AnimatedSprite::SetFrameSpeed(float f)
{
	m_frameSpeed = f;
}

void 
AnimatedSprite::SetFrameWidth(int w)
{
	m_frameWidth = w;
}

void 
AnimatedSprite::Pause()
{
	m_paused = !m_paused;
}

bool  
AnimatedSprite::IsPaused()
{
	return (m_paused);
}

bool 
AnimatedSprite::IsAnimating()
{
	return (m_animating);
}

void 
AnimatedSprite::StartAnimating()
{
	m_animating = true;

	m_timeElapsed = 0;
	m_currentFrame = 0;
}

bool 
AnimatedSprite::IsLooping()
{
	return (m_loop);
}

void 
AnimatedSprite::SetLooping(bool b)
{
	m_loop = b;
}

int
AnimatedSprite::GetFrameWidth()
{
	return m_frameWidth;
}

int
AnimatedSprite::GetCurrentFrame()
{
	return m_currentFrame;
}

int
AnimatedSprite::GetX() const
{
	return m_x;
}

int
AnimatedSprite::GetY() const
{
	return m_y;
}