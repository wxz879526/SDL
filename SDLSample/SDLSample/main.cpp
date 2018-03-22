#include <windows.h>
#include "SDL.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Quit();

	return 0;
}