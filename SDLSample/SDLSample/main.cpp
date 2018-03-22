#include <windows.h>
#include <string>
#include "SDL.h"

SDL_Surface* load_image(std::string path)
{
	auto loadedImg = SDL_LoadBMP(path.c_str());
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

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	const int SCREEN_BPP = 32;

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return 1;

	auto screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	auto foreign = load_image("foreground.bmp");
	auto bk = load_image("background.bmp");

	apply_surface(0, 0, bk, screen);
	apply_surface(320, 0, bk, screen);
	apply_surface(0, 240, bk, screen);
	apply_surface(320, 240, bk, screen);

	apply_surface(180, 140, foreign, screen);

	SDL_Flip(screen);
	SDL_Delay(10000);
	
	SDL_Quit();

	return 0;
}