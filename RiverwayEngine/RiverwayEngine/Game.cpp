#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

// public

Game::Game()
{

}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0)
	{
		SDL_Log("Failed while initializing SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game", // Title
		100, //Top left X coordinate of window
		100, //Top left Y coordinate of window
		1024, // Window Width
		768, // Window Height
		0 //flags
	);

	if (!mWindow)
	{
		SDL_Log("Failed while initializing SDL Window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow, // Window for renderer
		-1, // Graphics driver. -1 = let SDL decide
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	
	if (!mRenderer)
	{
		SDL_Log("Failed while initializing SDL Renderer: %s", SDL_GetError());
		return false;
	}

	

	return true;
}

void Game::RunLoop()
{
	mIsRunning = true;

	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

// private

void Game::ProcessInput()
{
	// Handle window events

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	// Handle keyboard events

	// Get keyboard state
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// If escape is pressed, end program
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	// Set paddle direction
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
}

void Game::UpdateGame()
{
	// Limit framerate to 60fps
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	// Ticks since last frame, converted to seconds
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	mTicksCount = SDL_GetTicks();
	
	// clamp deltatime to stop jumps

	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// Use deltaTime in game stuff

	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		// clamp paddle pos
		if (mPaddlePos.y < thickness)
		{
			mPaddlePos.y = thickness;
		}
		else if (mPaddlePos.y > 768 - thickness - paddleH)
		{
			mPaddlePos.y = 768 - thickness - paddleH;
		}
	}
}

void Game::GenerateOutput()
{
	// setup
	SDL_SetRenderDrawColor(
		mRenderer,
		0, // R
		0, // G
		0, // B
		1 // A
	);

	SDL_RenderClear(mRenderer);

	// render game

	// draw walls
	SDL_SetRenderDrawColor(
		mRenderer,
		227, // R
		240, // G
		241, // B
		255 // A
	);
	// top wall
	SDL_Rect wall{
		0,
		0,
		1024,
		thickness
	};

	SDL_RenderFillRect(mRenderer, &wall);

	// bottom wall
	wall.y = 768 - thickness;

	SDL_RenderFillRect(mRenderer, &wall);

	// right wall
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 768;

	SDL_RenderFillRect(mRenderer, &wall);

	// draw paddle

	SDL_SetRenderDrawColor(
		mRenderer,
		0, // R
		200, // G
		50, // B
		255 // A
	);

	SDL_Rect paddle{
		mPaddlePos.x,
		mPaddlePos.y,
		thickness,
		paddleH
	};

	SDL_RenderFillRect(mRenderer, &paddle);

	// swap buffers

	SDL_RenderPresent(mRenderer);
}
