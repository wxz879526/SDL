/*!
 * \file main.cpp
 * \date 2018/03/23 9:34
 *
 * \author wenxinzhou
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: input long description
 *
 * \note
*/

#include <windows.h>
#include <tchar.h>
#include <string>
#include <array>
#include <memory>
#include "SDL.h"
#include "SDL_image.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class LTexture {
public:
	LTexture();
	~LTexture();

	bool loadFromFile(std::string path);

	void free();

	void render(int x, int y);

	int getWidth();
	int getHeight();

private:
	SDL_Texture *m_texture{ nullptr };

	int mWidth{ 0 };
	int mHeight{ 0 };
};

SDL_Window *gWindow;
SDL_Texture *gTexture;
SDL_Renderer *gRender;

LTexture::LTexture()
{

}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	free();

	SDL_Surface *loadedSurface = IMG_Load(path.c_str());

	SDL_SetColorKey(loadedSurface, SDL_TRUE,
		SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
	auto pNewTexture = SDL_CreateTextureFromSurface(gRender, loadedSurface);
	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

	SDL_FreeSurface(loadedSurface);
	
	m_texture = pNewTexture;
	return true;
}

void LTexture::free()
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		mWidth = mHeight = 0;
	}
}

void LTexture::render(int x, int y)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy(gRender, m_texture, nullptr, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

LTexture gFooter;
LTexture gBackgnd;

SDL_Texture* loadTexure(std::string path)
{
	SDL_Texture *newTexture = nullptr;
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());

	newTexture = SDL_CreateTextureFromSurface(gRender,
		loadedSurface);

	SDL_FreeSurface(loadedSurface);
	return newTexture;
}


bool Init()
{
	bool bSuccess = true;

	if (SDL_Init(SDL_INIT_VIDEO))
	{
		bSuccess = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Tutorial",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (!gWindow)
		{
			bSuccess = false;
		}
		else
		{
			gRender = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

			SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
			int imgFlags = IMG_INIT_PNG;
			IMG_Init(imgFlags);
			//gScreen = SDL_GetWindowSurface(gWindow);
		}
	}

	return bSuccess;
}

bool loadMedia()
{
	gTexture = loadTexure("viewport.png");
	gFooter.loadFromFile("foo.png");
	gBackgnd.loadFromFile("background.png");
	return true;
}

void close()
{
	SDL_DestroyTexture(gTexture);
	gTexture = nullptr;

	SDL_DestroyRenderer(gRender);
	gRender = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	IMG_Quit();
	SDL_Quit();
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	if (!Init())
		return -1;

	loadMedia();

	bool quit = false;

	SDL_Event e;

	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRender);

		gBackgnd.render(0, 0);

		gFooter.render(100, 100);

		SDL_RenderPresent(gRender);
	}

	close();
	
	return 0;
}