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

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAILT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};


SDL_Window *gWindow;
SDL_Surface *gScreen;
SDL_Surface *gCurrentSurface;

SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

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

	return bSuccess;
}

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface *pOrgin = SDL_LoadBMP(path.c_str());
	SDL_Surface *pOpt = SDL_ConvertSurface(pOrgin, gScreen->format, 0);
	SDL_FreeSurface(pOrgin);
	return pOpt;
}

bool loadMedia()
{
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAILT] = loadSurface("press.bmp");
	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
	return true;
}

void close()
{
	for (int i =  0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
	{
		SDL_FreeSurface(gKeyPressSurfaces[i]);
		gKeyPressSurfaces[i] = nullptr;
	}

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
	gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAILT];

	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
					break;
				case SDLK_DOWN:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
					break;
				case SDLK_LEFT:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
					break;
				case SDLK_RIGHT:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
					break;
				default:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAILT];
				}
			}
		}

		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = SCREEN_WIDTH;
		stretchRect.h = SCREEN_HEIGHT;

		SDL_BlitScaled(gCurrentSurface, NULL, gScreen, &stretchRect);
		SDL_UpdateWindowSurface(gWindow);
	}


	close();
	
	return 0;
}