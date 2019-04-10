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

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *gWindow;
SDL_Surface *gImage;
SDL_Surface *gImage2;
SDL_Surface *gScreen;

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
			gScreen = SDL_GetWindowSurface(gWindow);
		}
	}

	return true;
}

bool loadMedia()
{
	gImage = SDL_LoadBMP("1.bmp");
	gImage2 = SDL_LoadBMP("2.bmp");
	return gImage != nullptr;
}

void close()
{
	SDL_FreeSurface(gImage);
	gImage = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

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

		SDL_BlitSurface(gImage, nullptr, gScreen, nullptr);

		SDL_Rect dest;
		dest.x = 100;
		dest.y = 100;
		dest.w = 100;
		dest.h = 100;
		SDL_BlitSurface(gImage2, nullptr, gScreen, &dest);
		SDL_UpdateWindowSurface(gWindow);
	}


	close();
	
	return 0;
}