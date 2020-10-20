#include "Game.h"

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
		748, // Window Height
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
}

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{
	// setup
	SDL_SetRenderDrawColor(
		mRenderer,
		39, // R
		174, // G
		96, // B
		255 // A
	);

	SDL_RenderClear(mRenderer);

	// render game

	SDL_SetRenderDrawColor(
		mRenderer,
		227, // R
		240, // G
		241, // B
		255 // A
	);

	SDL_Rect wall{
		10, // Top left X
		10, // Top left Y
		100, // Width
		100 // Height
	};

	SDL_RenderFillRect(mRenderer, &wall);

	// swap buffers

	SDL_RenderPresent(mRenderer);
}
