#include <windows.h>
#include "SDL.h"

void ShowPicture()
{
	auto screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);

	auto picture = SDL_LoadBMP("helloworld.bmp");

	SDL_BlitSurface(picture, nullptr, screen, nullptr);

	SDL_Flip(screen);

	SDL_Delay(10000);

	SDL_FreeSurface(picture);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	ShowPicture();
	
	SDL_Quit();

	return 0;
}