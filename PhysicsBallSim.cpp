#include <SDL.h>
#undef main

#include <box2d/box2d.h>
#include <iostream>

int main()
{
	//Create world with gravity
	b2Vec2 gravity(0.0f, -10.0f);
	b2World world(gravity);

	//Create body definition for the ground and set its inital position
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	//Create a ground body using the body definition
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	//Initialize SDL and create a window and renderer
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialize SDL2 library." << SDL_GetError << "\n";
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Event event;
	
	//Check if window and renderer were created properly
	if (window == NULL)
	{
		std::cout << "Failed to initialize window." << SDL_GetError << "\n";
		return -1;
	}

	if (renderer == NULL)
	{
		std::cout << "Failed to initialize renderer." << SDL_GetError << "\n";
		return -1;
	}

	//Main loop
	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = false;
		}
		//Render stuff here
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}