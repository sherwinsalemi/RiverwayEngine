#pragma once

#define SDL_MAIN_HANDLED

#include <SDL.h>

struct Vector2
{
	float x;
	float y;
};

class Game
{
public:
	Game();
	// Initialize game. Bool = true if success, false if fail
	bool Initialize();
	// Start the game loop until the game is over
	void RunLoop();
	// Shutdown the game
	void Shutdown();
private:
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// The window made by SDL
	SDL_Window* mWindow;
	// The renderer made by SDL
	SDL_Renderer* mRenderer;
	// Whether the game should continue to run
	bool mIsRunning;
	
	// Total ticks since the last frame, used for deltaTime
	Uint32 mTicksCount;

	// Which way to move paddle
	int mPaddleDir;

	// paddle and ball positions
	Vector2 mPaddlePos;
	Vector2 mBallPos;
};