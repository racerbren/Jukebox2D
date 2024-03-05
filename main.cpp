#include <iostream>
#include <SDL2/SDL.h>
#undef main

#define playback 0
#define recording 1

int main() 
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		std::cout << "ERROR: failed to initialize SDL.\n" << SDL_GetError();
		exit(EXIT_FAILURE);
	}
	
	SDL_Quit();

	return EXIT_SUCCESS;
}