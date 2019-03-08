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


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	SDL_Window *window = nullptr;
	SDL_Surface *screenSurface = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		MessageBox(NULL, _T("123"), _T("title"), MB_OK);
		return -1;
	}
	else
	{
		window = SDL_CreateWindow("SDL learn", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (nullptr == window)
		{
			MessageBox(NULL, _T("create window failed"), _T("title"), MB_OK);
			return -1;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);

			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));
			SDL_UpdateWindowSurface(window);
			SDL_Delay(20000);
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();


	return 0;
}