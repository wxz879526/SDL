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
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_events.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

SDL_Surface *g_bkImage;
SDL_Surface *g_screen;

SDL_Event g_event;


SDL_Surface* load_image(std::string path)
{
	auto loadedImg = IMG_Load(path.c_str());
	if (loadedImg != nullptr)
	{
		auto optimizedImg = SDL_DisplayFormat(loadedImg);

		SDL_FreeSurface(loadedImg);

		return optimizedImg;
	}

	return nullptr;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* dest)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, nullptr, dest, &offset);
}

bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		return false;

	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	if (nullptr == g_screen)
		return false;

	SDL_WM_SetCaption("Event Test", nullptr);

	return true;
}

bool load_files()
{
	g_bkImage = load_image("look.png");
	if (nullptr == g_bkImage)
		return false;

	return true;
}

void cleanup()
{
	SDL_FreeSurface(g_bkImage);

	SDL_Quit();
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{

	if (!init())
		return -1;

	if (!load_files())
		return -1;

	apply_surface(0, 0, g_bkImage, g_screen);

	if (SDL_Flip(g_screen) == -1)
		return -1;

	auto quitFlag = false;
	while (!quitFlag)
	{
		while (SDL_PollEvent(&g_event))
		{
			if (SDL_QUIT == g_event.type)
			{
				quitFlag = true;
			}
		}
	}

	cleanup();

	return 0;
}