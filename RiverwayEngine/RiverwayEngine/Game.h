#pragma once

#define SDL_MAIN_HANDLED

#include <SDL.h>

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
};