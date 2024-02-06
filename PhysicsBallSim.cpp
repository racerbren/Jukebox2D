#include "PhysicalBallSim.h"

int main()
{
	//Create body definition for the ground and set its inital position
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(400.0f, 800.0f);

	//Create a ground body using the body definition
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	//Create a box shape for the ground
	b2PolygonShape groundBox;
	groundBox.SetAsBox(400.0f, 50.0f);

	//Assign the fixture to the ground
	groundBody->CreateFixture(&groundBox, 0.0f);

	//Create a rigid body based on a body definition
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(400.0f, 400.0f);
	b2Body* body = world.CreateBody(&bodyDef);

	//Create a box shape for the rigid body
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(100.0f, 100.0f);

	//Give the body a fixture definition with the box shape, density, and friction
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	//Assign the fixture to the rigid body
	body->CreateFixture(&fixtureDef);

	//Create the timestep for physics simulation
	float timeStep = 1.0f / 60.0f;

	//Specify the amount of iterations to loop when stepping
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	//Initialize SDL and create a window and renderer
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)	
	{
		std::cout << "Failed to initialize SDL2 library." << SDL_GetError << "\n";
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	
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
		SDL_RenderClear(renderer);
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = false;
		}
		//Render stuff here
		b2Vec2 ballPosition;
		b2Vec2 groundPosition;
		for (int i = 0; i < 60; ++i)
		{
			world.Step(timeStep, velocityIterations, positionIterations);
			ballPosition = body->GetPosition();
			groundPosition = groundBody->GetPosition();
		}
		drawBall(renderer, ballPosition.x - 100, ballPosition.y - 100, 200, 200);
		drawFloor(renderer, groundPosition.x - 400, groundPosition.y - 50, 800, 50);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}