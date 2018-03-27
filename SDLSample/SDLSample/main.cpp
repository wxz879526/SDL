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
#include <array>
#include <memory>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_events.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

SDL_Surface* g_dot;
SDL_Surface* g_screen;
SDL_Surface* g_message;

TTF_Font* g_font;

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

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* dest, SDL_Rect *clip)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, dest, &offset);
}

bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		return false;

	if (TTF_Init() == -1)
		return false;

	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	if (nullptr == g_screen)
		return false;

	SDL_WM_SetCaption("Event Test", nullptr);

	return true;
}

bool load_files()
{
	g_dot = load_image("dots.png");
	if (nullptr == g_dot)
		return false;

	g_font = TTF_OpenFont("lazy.ttf", 28);
	if (nullptr == g_font)
		return false;

	return true;
}

void cleanup()
{
	SDL_FreeSurface(g_dot);
	SDL_FreeSurface(g_message);

	TTF_CloseFont(g_font);

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

	std::array<SDL_Rect, 4> clips;
	clips[0].x = 0;
	clips[0].y = 0;
	clips[0].w = 100;
	clips[0].h = 100;

	clips[1].x = 100;
	clips[1].y = 0;
	clips[1].w = 100;
	clips[1].h = 100;

	clips[2].x = 0;
	clips[2].y = 100;
	clips[2].w = 100;
	clips[2].h = 100;

	clips[3].x = 100;
	clips[3].y = 100;
	clips[3].w = 100;
	clips[3].h = 100;

	SDL_FillRect(g_screen, &g_screen->clip_rect, SDL_MapRGB(g_screen->format, 0xFF, 0xFF, 0xFF));

	apply_surface(0, 0, g_dot, g_screen, &clips[0]);
	apply_surface(540, 0, g_dot, g_screen, &clips[1]);
	apply_surface(0, 380, g_dot, g_screen, &clips[2]);
	apply_surface(540, 380, g_dot, g_screen, &clips[3]);

	SDL_Color textClr{ 0, 0, 0 };

	g_message = TTF_RenderText_Solid(g_font, "wenxinzhou xxxxxx j", textClr);

	apply_surface(150, 150, g_message, g_screen, nullptr);

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