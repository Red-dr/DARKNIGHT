// COMP710 GP 2D Framework 2018

// This include:
#include "backbuffer.h"

// Local includes:
#include "logmanager.h"
#include "texturemanager.h"
#include "sprite.h"
#include "texture.h"
#include "animatedsprite.h"

// Library includes:
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>

BackBuffer::BackBuffer()
: m_pTextureManager(0)
, m_pWindow(0)
, m_pRenderer(0)
, m_width(0)
, m_height(0)
, m_clearRed(0xFF)
, m_clearGreen(0xFF)
, m_clearBlue(0xFF)
{

}

BackBuffer::~BackBuffer()
{
	delete m_pTextureManager;
	m_pTextureManager = 0;

	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = 0;

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = 0;

	delete m_pTextureManager;
	m_pTextureManager = 0;


	IMG_Quit();
	SDL_Quit();
}

bool 
BackBuffer::Initialise(int width, int height)
{
	m_width = width;
	m_height = height;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		LogSDLError();
		return (false);
	}
	else
	{
		m_pWindow = SDL_CreateWindow("COMP710 2D Game Framework", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

		if (m_pWindow == 0)
		{
			LogSDLError();
			return (false);
		}
		else
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED); 

			if (m_pRenderer == 0)
			{
				LogSDLError();
				return (false);
			}
			else
			{
				int imageResult = IMG_Init(IMG_INIT_PNG);

				if (imageResult == 0)
				{
					LogSDLError();
					return (false);
				}
			}
		}
	}

	m_pTextureManager = new TextureManager();
	assert(m_pTextureManager);
	m_pTextureManager->Initialise(m_pRenderer);

	return (true);
}

void 
BackBuffer::Clear()
{
	SDL_SetRenderDrawColor(m_pRenderer, m_clearRed, m_clearGreen, m_clearBlue, 0xff);
	SDL_RenderClear(m_pRenderer);
}

void
BackBuffer::Present()
{
	SDL_RenderPresent(m_pRenderer);
}

void
BackBuffer::SetDrawColour(unsigned char r, unsigned char g, unsigned char b)
{
	SetDrawColour(r, g, b, 0xFF);
}

void
BackBuffer::SetDrawColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	SDL_SetRenderDrawColor(m_pRenderer, r, g, b, a);
}

void 
BackBuffer::DrawSprite(Sprite& sprite)
{

	SDL_Rect dest;

	dest.x = sprite.GetX();
	dest.y = sprite.GetY();
	dest.w = sprite.GetWidth();
	dest.h = sprite.GetHeight();

	SDL_RenderCopy(m_pRenderer, sprite.GetTexture()->GetTexture(), 0, &dest);
}

void
BackBuffer::DrawSprite(Sprite& sprite, int x , int y )
{

	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = sprite.GetWidth();
	dest.h = sprite.GetHeight();

	SDL_RenderCopy(m_pRenderer, sprite.GetTexture()->GetTexture(), 0, &dest);
}
void
BackBuffer::DrawAnimatedSprite(AnimatedSprite& animatedSprite)
{
	SDL_Rect dest;
	SDL_Rect sorcFrame;
	
	
	sorcFrame.x = animatedSprite.GetCurrentFrame() * animatedSprite.GetFrameWidth();//todo get current frame * frame width
	sorcFrame.y =0;
	sorcFrame.w = animatedSprite.GetFrameWidth();
	sorcFrame.h = animatedSprite.GetHeight();
	
	dest.x = animatedSprite.GetX();
	dest.y = animatedSprite.GetY();
	dest.w = animatedSprite.GetFrameWidth();
	dest.h = animatedSprite.GetHeight();
	
	

	SDL_RenderCopy(m_pRenderer, animatedSprite.GetTexture()->GetTexture(), &sorcFrame, &dest);
}

void BackBuffer::DrawAnimatedSprite(AnimatedSprite & animatedSprite, int x, int y)
{
	SDL_Rect dest;
	SDL_Rect sorcFrame;

	sorcFrame.x = animatedSprite.GetCurrentFrame() * animatedSprite.GetFrameWidth();//todo get current frame * frame width
	sorcFrame.y = 0;
	sorcFrame.w = animatedSprite.GetFrameWidth();
	sorcFrame.h = animatedSprite.GetHeight();

	dest.x = x;
	dest.y = y;
	dest.w = animatedSprite.GetFrameWidth();
	dest.h = animatedSprite.GetHeight();

	SDL_RenderCopy(m_pRenderer, animatedSprite.GetTexture()->GetTexture(), &sorcFrame, &dest);
}

void BackBuffer::DrawAnimatedSpriteFliped(AnimatedSprite & animatedSprite, int x, int y)
{
	SDL_Rect dest;
	SDL_Rect sorcFrame;

	sorcFrame.x = animatedSprite.GetCurrentFrame() * animatedSprite.GetFrameWidth();//todo get current frame * frame width
	sorcFrame.y = 0;
	sorcFrame.w = animatedSprite.GetFrameWidth();
	sorcFrame.h = animatedSprite.GetHeight();

	dest.x = x;
	dest.y = y;
	dest.w = animatedSprite.GetFrameWidth();
	dest.h = animatedSprite.GetHeight();

	SDL_RendererFlip flipstate = SDL_FLIP_HORIZONTAL;
	

	SDL_RenderCopyEx(m_pRenderer, animatedSprite.GetTexture()->GetTexture(), &dest, &sorcFrame, NULL, NULL, flipstate);
}

void
BackBuffer::DrawRectangle(int x1, int y1, int x2, int y2)
{
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect fillRect;
	
	
	fillRect.x = x1;
	fillRect.y = y1;
	fillRect.w = x2;
	fillRect.h = y2;

	SDL_RenderFillRect(m_pRenderer, &fillRect);
}

void
BackBuffer::DrawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(m_pRenderer, x1, y1, x2, y2);
}

void 
BackBuffer::LogSDLError()
{
	LogManager::GetInstance().Log(SDL_GetError());
}

Sprite* 
BackBuffer::CreateSprite(const char* pcFilename)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(pcFilename);

	Sprite* pSprite = new Sprite();
	if (!pSprite->Initialise(*pTexture))
	{
		LogManager::GetInstance().Log("Sprite Failed to Create!");
	}

	return (pSprite);
}

AnimatedSprite*
BackBuffer::CreateAnimatedSprite(const char* pcFilename)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(pcFilename);

	AnimatedSprite* pAnimatedSprite = new AnimatedSprite();
	if (!pAnimatedSprite->Initialise(*pTexture))
	{
		LogManager::GetInstance().Log("animaded sprite failed to create!");

	}
	return (pAnimatedSprite);
}


void 
BackBuffer::SetClearColour(unsigned char r, unsigned char g, unsigned char b)
{
	m_clearRed = r;
	m_clearGreen = g;
	m_clearBlue = b;
}
