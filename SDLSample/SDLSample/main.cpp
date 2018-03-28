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

SDL_Surface* g_screen;
SDL_Surface* g_backgnd;
SDL_Surface* g_message;
SDL_Surface* g_upMessage;
SDL_Surface* g_downMessage;
SDL_Surface* g_leftMessage;
SDL_Surface* g_rightMessage;

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
	g_backgnd = load_image("background.png");
	if (!g_backgnd)
		return false;

	g_font = TTF_OpenFont("lazy.ttf", 28);
	if (nullptr == g_font)
		return false;

	return true;
}

void cleanup()
{
	SDL_FreeSurface(g_upMessage);
	SDL_FreeSurface(g_downMessage);
	SDL_FreeSurface(g_leftMessage);
	SDL_FreeSurface(g_rightMessage);

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

	SDL_FillRect(g_screen, &g_screen->clip_rect, SDL_MapRGB(g_screen->format, 0xFF, 0xFF, 0xFF));

	SDL_Color textClr{ 0, 0, 0 };

	g_upMessage = TTF_RenderText_Solid(g_font, "Up was pressed", textClr);
	g_downMessage = TTF_RenderText_Solid(g_font, "Down was pressed", textClr);
	g_leftMessage = TTF_RenderText_Solid(g_font, "Left was pressed", textClr);
	g_rightMessage = TTF_RenderText_Solid(g_font, "Right was pressed", textClr);

	apply_surface(0, 0, g_backgnd, g_screen, nullptr);

	auto quitFlag = false;
	while (!quitFlag)
	{
		if (SDL_PollEvent(&g_event))
		{
			if (SDL_KEYDOWN == g_event.type)
			{
				switch (g_event.key.keysym.sym)
				{
				case SDLK_UP:
					g_message = g_upMessage;
					break;
				case SDLK_DOWN:
					g_message = g_downMessage;
					break;
				case SDLK_LEFT:
					g_message = g_leftMessage;
					break;
				case SDLK_RIGHT:
					g_message = g_rightMessage;
					break;
				}
			}
			if (SDL_QUIT == g_event.type)
			{
				quitFlag = true;
			}
		}

		if (g_message != nullptr)
		{
			apply_surface(0, 0, g_backgnd, g_screen, nullptr);
			apply_surface((SCREEN_WIDTH - g_message->w) / 2, (SCREEN_HEIGHT - g_message->h) / 2, g_message, g_screen, nullptr);
			g_message = nullptr;
		}

		if (SDL_Flip(g_screen) == -1)
			return -1;
	}

	cleanup();

	return 0;
}